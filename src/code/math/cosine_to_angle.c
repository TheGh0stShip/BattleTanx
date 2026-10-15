#include "types.h"

extern f32 gCosineTable[] __asm__("D_80139720");
extern f32 gCosineTableNext[] __asm__("D_80139724");

u16 cosine_to_angle(f32 value) __asm__("func_800F3BE4");

u16 cosine_to_angle(f32 value)
{
    u16 index;
    u16 step;
    s32 probe;
    f64 fraction;
    f32 unused[2];

    if (value == -1.0f) {
        index = 0x80;
    } else {
        index = 0;
        step = 0x40;
        while ((value < gCosineTableNext[index]) & (step != 0)) {
            index = probe = index ^ step;
            if (gCosineTableNext[probe - 1] < value) {
                index ^= step;
            }
            step >>= 1;
        }
    }
    fraction = (gCosineTable[index] - value) * 256.0 /
               (gCosineTable[index] - gCosineTableNext[index]);
    return (index << 8) + (u32)fraction;
}
