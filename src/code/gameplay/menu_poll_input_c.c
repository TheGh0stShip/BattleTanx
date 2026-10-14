#include "types.h"

s32 func_80096920(s32, s32);
extern s8 D_80327E31;

s32 menu_poll_input_c(void) __asm__("func_800C36E8");

s32 menu_poll_input_c(void) {
    s32 buttons;
    s32 result;

    buttons = func_80096920(0, 0);
    result = 0;
    if (buttons & 0x40) {
        result = 1;
    }
    D_80327E31 = 0;
    if (buttons & 0x10) {
        D_80327E31 = 1;
    }
    return result;
}
