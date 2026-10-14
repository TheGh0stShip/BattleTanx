#include "types.h"

#ifndef NULL
#define NULL 0
#endif

s32 func_800796F0(s32, s32);
extern f64 D_80074D20;

void tick_effect_countdown(void *arg0, s32 *arg1) __asm__("func_800F0DE0");

void tick_effect_countdown(void *arg0, s32 *arg1) {
    f32 temp_f0;
    s32 temp_a0;

    temp_f0 = (f32) ((f64) (*(f32 *)((s8 *)(arg0) + (0x1C))) - D_80074D20);
    (*(f32 *)((s8 *)(arg0) + (0x1C))) = temp_f0;
    if (temp_f0 <= 0.0f) {
        temp_a0 = (*(s32 *)((s8 *)(arg0) + (0x24)));
        if (temp_a0 != -1) {
            func_800796F0(temp_a0, 0);
        }
        *arg1 = 2;
    }
}
