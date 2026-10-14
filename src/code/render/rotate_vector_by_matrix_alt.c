#include "types.h"

#ifndef NULL
#define NULL 0
#endif

void rotate_vector_by_matrix_alt(void *arg0, void *arg1, void *arg2) __asm__("func_800A7C7C");

void rotate_vector_by_matrix_alt(void *arg0, void *arg1, void *arg2) {
    (*(f32 *)((s8 *)(arg2) + (0))) = (f32) (((*(f32 *)((s8 *)(arg1) + (0))) * (*(f32 *)((s8 *)(arg0) + (0)))) + ((*(f32 *)((s8 *)(arg1) + (4))) * (*(f32 *)((s8 *)(arg0) + (0x10)))) + ((*(f32 *)((s8 *)(arg1) + (8))) * (*(f32 *)((s8 *)(arg0) + (0x20)))));
    (*(f32 *)((s8 *)(arg2) + (4))) = (f32) (((*(f32 *)((s8 *)(arg1) + (0))) * (*(f32 *)((s8 *)(arg0) + (4)))) + ((*(f32 *)((s8 *)(arg1) + (4))) * (*(f32 *)((s8 *)(arg0) + (0x14)))) + ((*(f32 *)((s8 *)(arg1) + (8))) * (*(f32 *)((s8 *)(arg0) + (0x24)))));
    (*(f32 *)((s8 *)(arg2) + (8))) = (f32) (((*(f32 *)((s8 *)(arg1) + (0))) * (*(f32 *)((s8 *)(arg0) + (8)))) + ((*(f32 *)((s8 *)(arg1) + (4))) * (*(f32 *)((s8 *)(arg0) + (0x18)))) + ((*(f32 *)((s8 *)(arg1) + (8))) * (*(f32 *)((s8 *)(arg0) + (0x28)))));
}
