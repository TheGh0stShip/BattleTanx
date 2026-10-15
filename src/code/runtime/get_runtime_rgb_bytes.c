#include "types.h"

extern u8 gRuntimeRed __asm__("D_801257C4");
extern u8 gRuntimeGreen __asm__("D_801257C5");
extern u8 gRuntimeBlue __asm__("D_801257C6");

void get_runtime_rgb_bytes(u8 *red, u8 *green, u8 *blue) __asm__("func_8007D48C");

void get_runtime_rgb_bytes(u8 *red, u8 *green, u8 *blue)
{
    *red = gRuntimeRed;
    *green = gRuntimeGreen;
    *blue = gRuntimeBlue;
}
