#include "types.h"

extern s32 func_80096920(s32, s32);
extern s8 D_80327EB2;

s32 menu_poll_input_d(void) __asm__("func_800C4DFC");

s32 menu_poll_input_d(void) {
    s32 buttons = func_80096920(0, 0);
    s32 mask = buttons & 0x40;
    s32 flag = buttons & 0x10;
    s32 result;

    result = mask != 0;
    D_80327EB2 = 0;
    if (flag) {
        D_80327EB2 = 1;
    }
    return result;
}
