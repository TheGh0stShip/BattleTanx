#include "types.h"

typedef struct MotionBody {
    u16 flags;
    s16 x;
    s16 z;
    u8 pad06[8];
    s16 radius;
    s16 value10;
} MotionBody;

typedef struct EffectMotion {
    u16 mode;
    s16 next;
    s16 prev;
    u8 pad06[0x2];
    s32 owner;
    MotionBody body;
    u16 cellLinks[4];
    u8 pad26[0x2];
} EffectMotion;

extern s32 D_80142B50[4];
extern s32 D_80142B60[4];
extern u16 D_803B75B0[4][20][20];
extern s32 D_803B8234;
extern s32 D_803B8238;
extern s32 D_803B823C;
extern s32 D_803B8240;
extern EffectMotion D_803B8248[];
extern s32 D_803C4D68;

s32 create_point_motion(s32 owner, s32 x, s32 y, s16 radius,
                        u16 mode) __asm__("func_80106F94");

s32 create_point_motion(s32 owner, s32 x, s32 y, s16 radius,
                        u16 mode)
{
    s32 index;
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
    px = x;
    x += D_803B8238;
    D_803C4D68++;
    py = y;
    index = D_803B8234;
    D_803B8234 = D_803B8248[index].next;
    D_803B8248[D_803B8234].prev = -1;
    y += D_803B823C;
    if (D_803B8240 != -1) {
        D_803B8248[D_803B8240].prev = index;
    }
    D_803B8248[index].prev = -1;
    D_803B8248[index].next = D_803B8240;
    D_803B8240 = index;
    motion = &D_803B8248[index];
    motion->body.x = px;
    motion->body.z = py;
    motion->body.value10 = 0;
    motion->body.flags = 0x10;
    motion->body.radius = radius;
    motion->mode = mode;
    motion->owner = owner;
    for (i = 0, layer = D_803B75B0[0]; i < 4; i++) {
        row = (x + D_80142B50[i]) >> 11;
        col = (y + D_80142B60[i]) >> 11;
        cell = (u16 *)(row * 40 + (u32)layer);
        motion->cellLinks[i] = cell[col];
        cell[col] = index;
        layer += 20;
    }
    return index;
}
