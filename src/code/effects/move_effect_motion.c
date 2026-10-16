#include "types.h"

typedef struct EffectMotion {
    u16 mode;
    s16 next;
    s16 prev;
    u8 pad06[0x2];
    s32 owner;
    u16 body0;
    s16 x;
    s16 y;
    u8 pad12[0xC];
    s16 cellLinks[4];
    u8 pad26[0x2];
} EffectMotion;

extern void set_record_halfwords(void *record, s32 first, s32 second, u16 third) __asm__("func_80109354");
extern s32 D_80142B50[4];
extern s32 D_80142B60[4];
extern s16 D_803B75B0[4][20][20];
extern s32 D_803B8238;
extern s32 D_803B823C;
extern EffectMotion D_803B8248[];

void move_effect_motion(s32 index, s32 x, s32 y, u16 third) __asm__("func_801074AC");

void move_effect_motion(s32 index, s32 x, s32 y, u16 third)
{
    u32 i;
    s32 found;
    s32 px, py, ox, oy;
    s32 orow, ocol, nrow, ncol;
    s16 *cell;
    u16 cur;
    EffectMotion *motion;

    if (index == -1 || x < -D_803B8238 || D_803B8238 < x || y < -D_803B823C ||
        D_803B823C < y) {
        return;
    }
    found = 0;
    px = x;
    py = y;
    x += D_803B8238;
    y += D_803B823C;
    motion = &D_803B8248[index];
    ox = motion->x + D_803B8238;
    oy = motion->y + D_803B823C;
    for (i = 0; i < 4; i++) {
        orow = (ox + D_80142B50[i]) >> 11;
        ocol = (oy + D_80142B60[i]) >> 11;
        nrow = (x + D_80142B50[i]) >> 11;
        ncol = (y + D_80142B60[i]) >> 11;
        if ((orow == nrow) & (ocol == ncol)) {
            continue;
        }
        {
            s16 (*layer)[20] = D_803B75B0[i];

            cell = (s16 *)(orow * 40 + (u32)layer) - -ocol;
        }
        cur = *cell;
        if (*cell == index) {
            *cell = D_803B8248[index].cellLinks[i];
            found = 1;
        } else {
            while (*cell != -1) {
                cell = (s16 *)(i * 2 + (u32)D_803B8248[(s16)cur].cellLinks);
                if (*cell == index) {
                    *cell = D_803B8248[index].cellLinks[i];
                    found = 1;
                    break;
                }
                cur = *cell;
            }
        }
        motion->cellLinks[i] = -1;
        if (!found) {
            return;
        }
        {
            s16 (*layer)[20] = D_803B75B0[i];
            s16 *dst = (s16 *)(nrow * 40 + (u32)layer) - -ncol;

            motion->cellLinks[i] = *dst;
            *dst = index;
        }
    }
    set_record_halfwords(&motion->body0, px, py, third);
}
