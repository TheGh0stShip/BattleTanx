#include "types.h"

extern u32 gRandomSeed __asm__("D_80139610");

f32 random_unit_average_pair(void) __asm__("func_800F3940");

f32 random_unit_average_pair(void)
{
    u32 seed;
    u32 seed2;
    f32 first;

    seed = gRandomSeed * 0x10DCD + 1;
    gRandomSeed = seed;
    first = (f32)seed / 4294967296.0f;
    seed2 = seed * 0x10DCD + 1;
    gRandomSeed = seed2;
    return (first + (f32)seed2 / 4294967296.0f) * 0.5f;
}
