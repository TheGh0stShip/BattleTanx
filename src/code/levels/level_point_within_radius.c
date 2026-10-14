#include "types.h"

extern s32 D_801C9174;

s32 level_point_within_radius(void *level, s32 index, f32 x, f32 z) __asm__("func_8008332C");

s32 level_point_within_radius(void *level, s32 index, f32 x, f32 z)
{
    void *record;
    f32 dx;
    f32 dz;

    record = (u8 *)level + (index * 0x2C + 0x584);
    dx = *(f32 *)((u8 *)record + 0x24) - x;
    dz = *(f32 *)((u8 *)record + 0x20) - z;
    if (dx * dx + dz * dz < (f32)D_801C9174) {
        return 1;
    }
    return 0;
}
