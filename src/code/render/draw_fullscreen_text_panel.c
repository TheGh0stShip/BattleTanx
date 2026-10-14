#include "types.h"

#ifndef NULL
#define NULL 0
#endif

s32 func_800F4DFC(s32 *, s32, s32, s32, s32, s32, s32, s32, s32);
s32 func_801054E0(s32);
s32 func_8010552C(s32, s32);
s32 func_8010555C(s32, s32, s32, s32);
s32 func_80105A50(s32 *, s32 *, s32, s32);
s32 func_8010698C(s32 *);
extern s32 D_800731B0;
extern s32 D_803276D4;

void draw_fullscreen_text_panel(void) __asm__("func_800ABFD0");

void draw_fullscreen_text_panel(void) {
    func_800F4DFC(&D_803276D4, 0, 0, 0x140, 0xF0, 0, 0, 0, 0xFF);
    func_8010698C(&D_803276D4);
    func_8010555C(0xC8, 0xC8, 0xC8, 0xFF);
    func_801054E0(1);
    func_8010552C(0, 0x55);
    func_80105A50(&D_803276D4, &D_800731B0, 0, 0x140);
}
