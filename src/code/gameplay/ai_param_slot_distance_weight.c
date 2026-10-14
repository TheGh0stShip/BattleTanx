#include "types.h"

#ifndef NULL
#define NULL 0
#endif

void *func_800E52A0(s16, u8);
extern f32 D_80074878;
extern f32 D_8007487C;
extern f32 D_80074880;

f32 ai_param_slot_distance_weight(void *arg0) __asm__("func_800E94D8");

f32 ai_param_slot_distance_weight(void *arg0) {
    f32 var_f2;
    u8 temp_a1;

    temp_a1 = (*(u8 *)((s8 *)((*(void **)((s8 *)(arg0) + (8)))) + (0x359)));
    if (temp_a1 == 0xFF) {
        var_f2 = D_80074878;
    } else {
        var_f2 = (*(f32 *)((s8 *)(func_800E52A0((*(s16 *)((s8 *)(arg0) + (0x18))), temp_a1)) + (8))) * D_8007487C;
    }
    return D_80074880 - var_f2;
}
