#include "types.h"

typedef struct Point2f {
    f32 x;
    f32 y;
} Point2f;

typedef struct SlotPos {
    u8 pad00[0x20];
    f32 x;
    f32 y;
    u8 pad28[0x4];
} SlotPos;

typedef struct SlotOwner {
    u8 pad00[0x584];
    SlotPos slots[1];
} SlotOwner;

extern s32 func_8007AAA0(void);
extern s32 func_800942A8(Point2f *quad, s32 count, SlotPos *slot);
extern s32 D_801C9174;

s32 slots_near_quad_outside_mask(SlotOwner *owner, Point2f *quad) __asm__("func_80084778");

static inline s32 within_radius(f32 px, f32 py, f32 x, f32 y) {
    f32 dy;
    f32 dx;
    s32 r;
    dy = y - py;
    dx = x - px;
    r = 0;
    if (dy * dy + dx * dx < (f32)D_801C9174) {
        r = 1;
    }
    return r;
}

s32 slots_near_quad_outside_mask(SlotOwner *owner, Point2f *quad) {
    s32 i;
    u8 mask;
    s32 count;
    s32 j;
    SlotPos *slot;

    i = 0;
    mask = 0;
    count = func_8007AAA0();
    while (i < count) {
        j = 0;
        slot = &owner->slots[i];
        for (; j < 4; j++) {
            if (within_radius(quad[j].x, quad[j].y, slot->x, slot->y)) {
                if (func_800942A8(quad, 4, slot) == 0) {
                    mask |= 1 << i;
                }
                break;
            }
        }
        i++;
    }
    return mask;
}
