#include "types.h"

extern f32 gAngleInterpScale __asm__("D_80074F54");
extern f32 gSineTable[] __asm__("D_80139620");

f32 angle_cos(u32 angle) __asm__("func_800F3B40");

f32 angle_cos(u32 angle) {
    u32 index = (((angle & 0xFFFF) >> 8) + 0x40) & 0xFF;
    u32 next = index + 1;
    f32 base = gSineTable[index];

    return base + (gSineTable[next] - base) * (f32)(s32)(angle & 0xFF) * gAngleInterpScale;
}
