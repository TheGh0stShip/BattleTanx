#include "types.h"

#ifndef NULL
#define NULL 0
#endif

s32 func_800983E0(void *, s32, u8, s32);
void *func_800A6688(u8);

void ai_award_kill_credit(void *arg0, void *arg1) __asm__("func_800E44EC");

void ai_award_kill_credit(void *arg0, void *arg1) {
    u16 temp_v1;
    u8 var_a0;
    void *temp_v0;

    if ((*(s32 *)((s8 *)(arg0) + (0x98))) != 0) {
        func_800983E0(arg1, 0x2710, (*(u8 *)((s8 *)(arg1) + (4))), 0);
        var_a0 = (*(u8 *)((s8 *)(arg1) + (4)));
        goto block_4;
    }
    if ((*(s32 *)((s8 *)(arg1) + (0x98))) != 0) {
        func_800983E0(arg0, 0x2710, (*(u8 *)((s8 *)(arg0) + (4))), 0);
        var_a0 = (*(u8 *)((s8 *)(arg0) + (4)));
block_4:
        temp_v0 = func_800A6688(var_a0);
        temp_v1 = (*(u16 *)((s8 *)(temp_v0) + (0x1AC)));
        if (temp_v1 < 0x2710U) {
            (*(u16 *)((s8 *)(temp_v0) + (0x1AC))) = (u16) (temp_v1 + 1);
        }
    }
}
