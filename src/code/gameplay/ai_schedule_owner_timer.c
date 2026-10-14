#include "types.h"

#ifndef NULL
#define NULL 0
#endif

s32 func_8007B1DC();
s32 func_8007B1EC(f32);
f32 func_800F3880(f32);
extern f32 D_800746DC;

s32 ai_schedule_owner_timer(void *arg0) __asm__("func_800E70DC");

s32 ai_schedule_owner_timer(void *arg0) {
    f32 temp_f12;
    s32 temp_s0;
    s32 temp_s0_2;
    s32 temp_s1;

    temp_s0 = (s32) (*(f32 *)((s8 *)(arg0) + (0x20)));
    temp_s1 = (s32) (*(f32 *)((s8 *)(arg0) + (0x24))) - temp_s0;
    temp_s0_2 = temp_s0 + func_8007B1DC();
    temp_f12 = (f32) temp_s1 * func_800F3880(D_800746DC);
    (*(s32 *)((s8 *)((*(void **)((s8 *)(arg0) + (4)))) + (0x198))) = temp_s0_2;
    (*(s32 *)((s8 *)((*(void **)((s8 *)(arg0) + (4)))) + (0x19C))) = (s32) (temp_s0_2 + func_8007B1EC(temp_f12));
    return -1;
}
