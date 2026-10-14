#include "types.h"

#ifndef NULL
#define NULL 0
#endif

s32 func_800E3470(s32);
extern f32 D_80074848;
extern f32 D_8007484C;

f32 ai_param_member_flag_inverse_weight(void *arg0) __asm__("func_800E9200");

f32 ai_param_member_flag_inverse_weight(void *arg0) {
    f32 var_f2;
    void *temp_a0;

    temp_a0 = (*(void **)((s8 *)(arg0) + (8)));
    if (((*(s32 *)((s8 *)(temp_a0) + (0xB4))) == 1) && (func_800E3470((*(s32 *)((s8 *)(temp_a0) + (0xC4)))) != 0)) {
        var_f2 = D_80074848;
    } else {
        var_f2 = 0.0f;
    }
    return D_8007484C - var_f2;
}
