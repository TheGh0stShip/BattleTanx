#include "types.h"

#ifndef NULL
#define NULL 0
#endif

s32 func_800E3470(s32);
extern f32 D_80074844;

f32 ai_param_member_flag_weight(void *arg0) __asm__("func_800E91AC");

f32 ai_param_member_flag_weight(void *arg0) {
    void *temp_a0;

    temp_a0 = (*(void **)((s8 *)(arg0) + (8)));
    if (((*(s32 *)((s8 *)(temp_a0) + (0xB4))) == 1) && (func_800E3470((*(s32 *)((s8 *)(temp_a0) + (0xC4)))) != 0)) {
        return D_80074844;
    }
    return 0.0f;
}
