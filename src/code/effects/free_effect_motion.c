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

extern s32 D_80142B50[4];
extern s32 D_80142B60[4];
extern s16 D_803B75B0[4][20][20];
extern u16 D_803B8230;
extern s32 D_803B8234;
extern s32 D_803B8238;
extern s32 D_803B823C;
extern s32 D_803B8240;
extern EffectMotion D_803B8248[];

void free_effect_motion(s32 index) __asm__("func_80107170");

void free_effect_motion(s32 index)
{
    s32 found;
    u32 i;
    s32 row, col;
    s16 (*layer)[20];
    s16 *cell;
    u16 node;
    u16 cur;
    s16 prev;
    s32 x, y;

    if (index == -1) {
        return;
    }
    found = 0;
    if (D_803B8248[index].prev != -1) {
        D_803B8248[D_803B8248[index].prev].next = D_803B8248[index].next;
        if (D_803B8248[index].next != -1) {
            D_803B8248[D_803B8248[index].next].prev = D_803B8248[index].prev;
        }
    } else {
        D_803B8240 = D_803B8248[index].next;
        if (D_803B8240 != -1) {
            D_803B8248[D_803B8240].prev = -1;
        }
    }
    D_803B8248[index].prev = -1;
    D_803B8248[index].next = D_803B8234;
    if (D_803B8234 != -1) {
        D_803B8248[D_803B8234].prev = index;
    }
    D_803B8234 = index;
    x = D_803B8248[index].x + D_803B8238;
    y = D_803B8248[index].y + D_803B823C;
    for (i = 0; i < 4; i++) {
        row = (x + D_80142B50[i]) >> 11;
        col = (y + D_80142B60[i]) >> 11;
        layer = D_803B75B0[i];
        cell = (s16 *)(row * 40 + (u32)layer) - -col;
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
        if (found) {
            D_803B8248[index].cellLinks[i] = -1;
        }
    }
    prev = -1;
    node = D_803B8230;
    while ((s16)node != -1) {
        if (index == (s16)node) {
            if ((s16)node == (s16)D_803B8230) {
                D_803B8230 = D_803B8248[(s16)node].cellLinks[0];
                D_803B8248[index].cellLinks[0] = -1;
                return;
            }
            if (prev != -1) {
                D_803B8248[prev].cellLinks[0] = D_803B8248[index].cellLinks[0];
            }
            D_803B8248[index].cellLinks[0] = -1;
            return;
        }
        prev = node;
        node = D_803B8248[(s16)node].cellLinks[0];
    }
}
