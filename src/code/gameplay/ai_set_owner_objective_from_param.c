#include "types.h"

#ifndef NULL
#define NULL 0
#endif

extern f32 D_800746D4;

s32 ai_set_owner_objective_from_param(void *arg0) __asm__("func_800E6FF8");

s32 ai_set_owner_objective_from_param(void *arg0) {
    f32 temp_f2;
    s32 var_v1;
    u32 var_v0;

    temp_f2 = (*(f32 *)((s8 *)(arg0) + (0x20)));
    if (!(D_800746D4 <= temp_f2)) {
        goto block_2;
    }
    goto block_4;
block_2:
    var_v1 = (s32) temp_f2;
    var_v0 = var_v1 & 0xFFFF;
    goto block_5;
block_4:
    var_v1 = (s32) (temp_f2 - D_800746D4) | 0x80000000;
    var_v0 = var_v1 & 0xFFFF;
block_5:
    if (var_v0 < 5U) {
        goto block_7;
    }
    (*(s16 *)((s8 *)((*(void **)((s8 *)(arg0) + (4)))) + (0x1A8))) = 0xFF;
    goto block_8;
block_7:
    (*(s16 *)((s8 *)((*(void **)((s8 *)(arg0) + (4)))) + (0x1A8))) = (s16) var_v1;
block_8:
    return -1;
}
