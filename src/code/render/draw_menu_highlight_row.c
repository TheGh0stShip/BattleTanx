#include "types.h"

#ifndef NULL
#define NULL 0
#endif

s32 func_8010552C(s32, s32);
s32 func_8010555C(s32, s32, s32, s32);
s32 func_80105584(s32 *, s32);
extern s32 D_8037A174;

void draw_menu_highlight_row(s32 arg0, s32 arg1) __asm__("func_800D18C4");

void draw_menu_highlight_row(s32 arg0, s32 arg1) {
    func_8010555C(0, 0xFF, 0, 0xFF);
    func_8010552C(0x2E, (arg0 * 0xC) + 0x3A);
    func_80105584(&D_8037A174, arg1);
}
