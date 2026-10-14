#include "types.h"

#ifndef NULL
#define NULL 0
#endif

s32 func_80096920(s32, s32);
extern u8 D_80327D2C;
extern s8 D_80327D2D;

u8 menu_poll_input_b(void) __asm__("func_800BFF68");

u8 menu_poll_input_b(void) {
    s32 temp_v0;

    temp_v0 = func_80096920(0, 0);
    if (temp_v0 & 0x40) {
        D_80327D2C = 1;
    }
    D_80327D2D = 0;
    if (temp_v0 & 0x10) {
        D_80327D2D = 1;
    }
    return D_80327D2C;
}
