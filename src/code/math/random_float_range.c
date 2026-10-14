#include "types.h"

extern s32 gRandomSeed __asm__("D_80139610");
extern f64 gUnsignedIntBias __asm__("D_80074F10");
extern f32 gUnsignedIntScale __asm__("D_80074F18");

f32 random_float_range(f32 range) __asm__("func_800F3880");

f32 random_float_range(f32 range)
{
    f64 value;
    s32 seed;

    seed = gRandomSeed * 0x10DCD + 1;
    value = (f64)seed;
    gRandomSeed = seed;
    if (seed < 0) {
        value += gUnsignedIntBias;
    }
    return ((f32)value / gUnsignedIntScale) * range;
}
