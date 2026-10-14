#include "types.h"

#ifndef NULL
#define NULL 0
#endif

s32 func_8010552C(s32, s32);
s32 func_8010555C(s32, s32, s32, s32);
s32 func_80105584(s32 *, s32 *);
extern s32 D_80073D08;
extern s32 D_8037A174;

void draw_menu_label_9(void) __asm__("func_800D1874");

void draw_menu_label_9(void) {
    func_8010555C(0xFF, 0xFF, 0xFF, 0xFF);
    func_8010552C(0x2E, 0x5E);
    func_80105584(&D_8037A174, &D_80073D08);
}
