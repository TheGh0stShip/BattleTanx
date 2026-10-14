#include "types.h"

#ifndef NULL
#define NULL 0
#endif

f32 func_800F3AE0(u16);
f32 func_800F3B40(u16);

void compute_rotated_quad(void *arg0, void *arg1) __asm__("func_8010A474");

void compute_rotated_quad(void *arg0, void *arg1) {
    f32 temp_f0;
    f32 temp_f20;

    temp_f20 = -func_800F3AE0((*(u16 *)((s8 *)(arg0) + (0x10))));
    temp_f0 = func_800F3B40((*(u16 *)((s8 *)(arg0) + (0x10))));
    (*(f32 *)((s8 *)(arg1) + (4))) = (f32) (((temp_f0 * (f32) (*(s16 *)((s8 *)(arg0) + (6)))) - (temp_f20 * (f32) (*(s16 *)((s8 *)(arg0) + (0xA))))) + (f32) (*(s16 *)((s8 *)(arg0) + (2))));
    (*(f32 *)((s8 *)(arg1) + (0))) = (f32) ((temp_f20 * (f32) (*(s16 *)((s8 *)(arg0) + (6)))) + (temp_f0 * (f32) (*(s16 *)((s8 *)(arg0) + (0xA)))) + (f32) (*(s16 *)((s8 *)(arg0) + (4))));
    (*(f32 *)((s8 *)(arg1) + (0xC))) = (f32) (((temp_f0 * (f32) (*(s16 *)((s8 *)(arg0) + (8)))) - (temp_f20 * (f32) (*(s16 *)((s8 *)(arg0) + (0xA))))) + (f32) (*(s16 *)((s8 *)(arg0) + (2))));
    (*(f32 *)((s8 *)(arg1) + (8))) = (f32) ((temp_f20 * (f32) (*(s16 *)((s8 *)(arg0) + (8)))) + (temp_f0 * (f32) (*(s16 *)((s8 *)(arg0) + (0xA)))) + (f32) (*(s16 *)((s8 *)(arg0) + (4))));
    (*(f32 *)((s8 *)(arg1) + (0x14))) = (f32) (((temp_f0 * (f32) (*(s16 *)((s8 *)(arg0) + (8)))) - (temp_f20 * (f32) (*(s16 *)((s8 *)(arg0) + (0xC))))) + (f32) (*(s16 *)((s8 *)(arg0) + (2))));
    (*(f32 *)((s8 *)(arg1) + (0x10))) = (f32) ((temp_f20 * (f32) (*(s16 *)((s8 *)(arg0) + (8)))) + (temp_f0 * (f32) (*(s16 *)((s8 *)(arg0) + (0xC)))) + (f32) (*(s16 *)((s8 *)(arg0) + (4))));
    (*(f32 *)((s8 *)(arg1) + (0x1C))) = (f32) (((temp_f0 * (f32) (*(s16 *)((s8 *)(arg0) + (6)))) - (temp_f20 * (f32) (*(s16 *)((s8 *)(arg0) + (0xC))))) + (f32) (*(s16 *)((s8 *)(arg0) + (2))));
    (*(f32 *)((s8 *)(arg1) + (0x18))) = (f32) ((temp_f20 * (f32) (*(s16 *)((s8 *)(arg0) + (6)))) + (temp_f0 * (f32) (*(s16 *)((s8 *)(arg0) + (0xC)))) + (f32) (*(s16 *)((s8 *)(arg0) + (4))));
}
