#include "types.h"

typedef struct EffectMotion {
    u16 mode;
    s16 next;
    s16 prev;
    u8 pad06[0x2];
    s32 owner;
    u8 body[0x12];
    u16 cellLinks[4];
    u8 pad26[0x2];
} EffectMotion;

extern void init_effect_motion_body(void *body, s32 x, s32 y, s32 minX, s32 maxX, s32 minY,
                                    s32 maxY, s32 flags) __asm__("func_80109268");
extern s32 D_80142B50[4];
extern s32 D_80142B60[4];
extern u16 D_803B75B0[4][20][20];
extern u16 D_803B8230;
extern s32 D_803B8234;
extern s32 D_803B8238;
extern s32 D_803B823C;
extern s32 D_803B8240;
extern EffectMotion D_803B8248[];
extern s32 D_803C4D68;

s32 create_effect_motion(s32 owner, s32 x, s32 y, s32 minX, s32 maxX, s32 minY, s32 maxY,
                         u16 mode, u16 flags) __asm__("func_80106D18");

s32 create_effect_motion(s32 owner, s32 x, s32 y, s32 minX, s32 maxX, s32 minY, s32 maxY,
                         u16 mode, u16 flags)
{
    s32 index;
    u16 old;
    s32 px;
    s32 py;
    u32 i;
    u16 *cell;
    s32 row;
    s32 col;
    u16 (*layer)[20];
    EffectMotion *motion;

    if (D_803B8234 == -1 || x < -D_803B8238 || D_803B8238 < x || y < -D_803B823C ||
        D_803B823C < y) {
        return -1;
    }
    D_803C4D68++;
    px = x;
    py = y;
    x += D_803B8238;
    y += D_803B823C;
    index = D_803B8234;
    D_803B8234 = D_803B8248[index].next;
    D_803B8248[D_803B8234].prev = -1;
    if (D_803B8240 != -1) {
        D_803B8248[D_803B8240].prev = index;
    }
    D_803B8248[index].prev = -1;
    D_803B8248[index].next = D_803B8240;
    D_803B8240 = index;
    motion = &D_803B8248[index];
    init_effect_motion_body(motion->body, px, py, minX, maxX, minY, maxY, flags);
    motion->mode = mode;
    motion->owner = owner;
    if (minX + maxX < 0x400 && minY + maxY < 0x400) {
        for (i = 0, layer = D_803B75B0[0]; i < 4; i++) {
            row = (x + D_80142B50[i]) >> 11;
            col = (y + D_80142B60[i]) >> 11;
            cell = (u16 *)(row * 40 + (u32)layer);
            motion->cellLinks[i] = cell[col];
            cell[col] = index;
            layer += 20;
        }
    } else {
        old = D_803B8230;
        D_803B8230 = index;
        motion->cellLinks[0] = old;
    }
    return index;
}
