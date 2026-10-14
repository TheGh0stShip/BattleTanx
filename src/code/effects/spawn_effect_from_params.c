#include "types.h"

#ifndef NULL
#define NULL 0
#endif

s32 func_800821C0();
s32 func_80084CC4(s32, s32, s32, s32, s32, s32, s32, f32);
extern f32 D_80071E90;

void spawn_effect_from_params(void *arg0) __asm__("func_80091D10");

void spawn_effect_from_params(void *arg0) {
    func_80084CC4(func_800821C0(), (*(s32 *)((s8 *)(arg0) + (0xC))), 0, (*(s32 *)((s8 *)(arg0) + (0x10))), 6, 0, (*(s32 *)((s8 *)(arg0) + (0x14))), D_80071E90);
}
