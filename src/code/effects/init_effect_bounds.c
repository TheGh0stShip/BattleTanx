#include "types.h"

#ifndef NULL
#define NULL 0
#endif

void init_effect_bounds(void *arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, s32 arg6) __asm__("func_80094060");

void init_effect_bounds(void *arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, s32 arg6) {
    (*(s8 *)((s8 *)(arg0) + (0x18))) = 0;
    (*(f32 *)((s8 *)(arg0) + (0))) = arg3;
    (*(f32 *)((s8 *)(arg0) + (0x10))) = (f32) -arg1;
    (*(f32 *)((s8 *)(arg0) + (4))) = arg4;
    (*(s32 *)((s8 *)(arg0) + (0x1C))) = arg6;
    (*(f32 *)((s8 *)(arg0) + (0x14))) = (f32) -arg2;
    (*(f32 *)((s8 *)(arg0) + (8))) = (f32) (arg3 * arg5);
    (*(f32 *)((s8 *)(arg0) + (0xC))) = (f32) (arg4 * arg5);
}
