#include "types.h"

#ifndef NULL
#define NULL 0
#endif

s32 func_80111540(s32 *, s32, s32 *, s32, s32 *, s32);
s32 func_801121E0();
s32 func_8011D1A0(s32 *);
extern s32 D_801499F0;
extern s32 D_8014B9F0;
extern s32 func_80077A38;

void boot_create_idle_thread(s32 arg0) __asm__("func_800779CC");

void boot_create_idle_thread(s32 arg0) {
    func_801121E0();
    func_80111540(&D_8014B9F0, 1, &func_80077A38, arg0, &D_801499F0, 0xF);
    func_8011D1A0(&D_8014B9F0);
}
