#include "types.h"

#ifndef NULL
#define NULL 0
#endif

extern u32 D_80139610;

s32 next_random_u32(void) __asm__("func_800F38F4");

s32 next_random_u32(void) {
    u32 temp_v0;

    temp_v0 = (D_80139610 * 0x10DCD) + 1;
    D_80139610 = temp_v0;
    return (temp_v0 << 0x10) | (temp_v0 >> 0x10);
}
