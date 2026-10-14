#include "types.h"

#ifndef NULL
#define NULL 0
#endif

void scale_matrix_axes(void *arg0, f32 arg1, f32 arg2, f32 arg3) __asm__("func_800A823C");

void scale_matrix_axes(void *arg0, f32 arg1, f32 arg2, f32 arg3) {
    (*(f32 *)((s8 *)(arg0) + (0))) = (f32) ((*(f32 *)((s8 *)(arg0) + (0))) * arg1);
    (*(f32 *)((s8 *)(arg0) + (4))) = (f32) ((*(f32 *)((s8 *)(arg0) + (4))) * arg1);
    (*(f32 *)((s8 *)(arg0) + (8))) = (f32) ((*(f32 *)((s8 *)(arg0) + (8))) * arg1);
    (*(f32 *)((s8 *)(arg0) + (0x10))) = (f32) ((*(f32 *)((s8 *)(arg0) + (0x10))) * arg2);
    (*(f32 *)((s8 *)(arg0) + (0x14))) = (f32) ((*(f32 *)((s8 *)(arg0) + (0x14))) * arg2);
    (*(f32 *)((s8 *)(arg0) + (0x18))) = (f32) ((*(f32 *)((s8 *)(arg0) + (0x18))) * arg2);
    (*(f32 *)((s8 *)(arg0) + (0x20))) = (f32) ((*(f32 *)((s8 *)(arg0) + (0x20))) * arg3);
    (*(f32 *)((s8 *)(arg0) + (0x24))) = (f32) ((*(f32 *)((s8 *)(arg0) + (0x24))) * arg3);
    (*(f32 *)((s8 *)(arg0) + (0x28))) = (f32) ((*(f32 *)((s8 *)(arg0) + (0x28))) * arg3);
}
