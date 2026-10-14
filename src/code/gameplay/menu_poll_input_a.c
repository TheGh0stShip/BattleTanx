#include "types.h"

#ifndef NULL
#define NULL 0
#endif

s32 func_80096920(s32, s32);
extern u8 D_80327C0F;
extern s8 D_80327C10;

u8 menu_poll_input_a(void) __asm__("func_800BC448");

u8 menu_poll_input_a(void) {
    s32 temp_v0;

    temp_v0 = func_80096920(0, 0);
    if (temp_v0 & 0x40) {
        D_80327C0F = 1;
    }
    D_80327C10 = 0;
    if (temp_v0 & 0x10) {
        D_80327C10 = 1;
    }
    return D_80327C0F;
}
