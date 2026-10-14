#include "types.h"

#ifndef NULL
#define NULL 0
#endif

s32 func_800798C0(s32);
s32 func_80096920(s32, s32);
extern u8 D_80327B20;
extern s8 D_80327B21;
extern s32 D_80327B34;

u8 menu_poll_input_with_sound(void) __asm__("func_800B8750");

u8 menu_poll_input_with_sound(void) {
    s32 temp_v0;

    temp_v0 = func_80096920(0, 0);
    if (temp_v0 & 0x40) {
        D_80327B20 = 1;
    }
    if (temp_v0 & 0x20) {
        D_80327B20 = 2;
    }
    D_80327B21 = 0;
    if (temp_v0 & 0x10) {
        D_80327B21 = 1;
    }
    if ((temp_v0 != 0) && (D_80327B34 != -1)) {
        func_800798C0(D_80327B34);
        D_80327B34 = -1;
    }
    return D_80327B20;
}
