#include "types.h"

#ifndef NULL
#define NULL 0
#endif

extern s32 D_80328150;
extern s8 D_80328158;
extern s8 D_80328159;

void menu_step_cursor(s32 arg0) __asm__("func_800D0CB4");

void menu_step_cursor(s32 arg0) {
    s32 temp_v0;
    s32 temp_v1;
    s32 var_a0;
    s32 var_v1;

    var_v1 = 0;
    if (arg0 & 1) {
        var_v1 = -1;
        D_80328158 = 8;
    }
    if (arg0 & 8) {
        var_v1 += 1;
        D_80328159 = 8;
    }
    temp_v0 = D_80328150 + var_v1;
    temp_v1 = temp_v0 & ((s32) ~temp_v0 >> 0x1F);
    D_80328150 = temp_v1;
    var_a0 = 0xF;
    if (temp_v1 < 0xF) {
        var_a0 = temp_v1;
    }
    D_80328150 = var_a0;
}
