#include "types.h"

#ifndef NULL
#define NULL 0
#endif

void *func_800A6688(u16);
extern f32 D_800747E8;
extern f32 D_800747EC;
extern f32 D_800747F0;

f32 ai_param_target_class_weight_b(void *arg0) __asm__("func_800E8B6C");

f32 ai_param_target_class_weight_b(void *arg0) {
    f32 var_f2;
    s32 temp_v1;
    u16 temp_a0;
    void *temp_v0;

    temp_a0 = (*(u16 *)((s8 *)((*(void **)((s8 *)(arg0) + (4)))) + (0x1A8)));
    if (temp_a0 == 0xFF) {
        goto block_7;
    }
    temp_v0 = func_800A6688(temp_a0);
    if ((*(u8 *)((s8 *)(temp_v0) + (0x1AF))) == 0) {
        goto block_7;
    }
    temp_v1 = (*(s32 *)((s8 *)((*(void **)((s8 *)(temp_v0) + (0x1B8)))) + (0x18)));
    if (temp_v1 == 0) {
        goto block_5;
    }
    if (temp_v1 == 1) {
        goto block_6;
    }
    goto block_7;
block_5:
    var_f2 = D_800747E8;
    goto block_8;
block_6:
    var_f2 = D_800747EC;
    goto block_8;
block_7:
    var_f2 = 0.0f;
block_8:
    return D_800747F0 - var_f2;
}
