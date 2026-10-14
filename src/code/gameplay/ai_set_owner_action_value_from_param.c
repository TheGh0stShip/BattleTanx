#include "types.h"

#ifndef NULL
#define NULL 0
#endif

extern f32 D_800746D8;

s32 ai_set_owner_action_value_from_param(void *arg0) __asm__("func_800E7064");

s32 ai_set_owner_action_value_from_param(void *arg0) {
    s32 temp_v1;
    void *temp_v0;

    temp_v1 = (*(s32 *)((s8 *)(arg0) + (0x40)));
    switch (temp_v1) {                              /* irregular */
    case 0:
        temp_v0 = (*(void **)((s8 *)(arg0) + (4)));
        (*(f32 *)((s8 *)(temp_v0) + (0x1A0))) = (f32) (*(f32 *)((s8 *)(temp_v0) + (0x32C)));
        break;
    case 1:
        (*(f32 *)((s8 *)((*(void **)((s8 *)(arg0) + (4)))) + (0x1A0))) = (f32) ((*(f32 *)((s8 *)(arg0) + (0x20))) * D_800746D8);
        break;
    }
    return -1;
}
