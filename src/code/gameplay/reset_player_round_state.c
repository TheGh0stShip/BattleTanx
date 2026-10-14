#include "types.h"

#ifndef NULL
#define NULL 0
#endif

s32 func_8007AAA0();
s32 func_80081A30();
s32 func_800821C0();
s32 func_8008228C(s32);
s32 func_80083394(s32);
s32 func_80083F04(s32);
void *func_800A424C(void *);
void *func_800A6688(s32);

void reset_player_round_state(void) __asm__("func_8007FF68");

void reset_player_round_state(void) {
    s32 temp_v0;
    s32 temp_v0_4;
    s32 var_s1;
    void *temp_v0_2;
    void *temp_v0_3;

    temp_v0 = func_8007AAA0();
    var_s1 = 0;
    if (temp_v0 > 0) {
        do {
            temp_v0_2 = func_800A6688(var_s1 & 0xFFFF);
            temp_v0_3 = func_800A424C(temp_v0_2);
            var_s1 += 1;
            (*(s32 *)((s8 *)(temp_v0_3) + (0x88))) = 0;
            (*(s32 *)((s8 *)(temp_v0_2) + (0x140))) = 0;
        } while ((var_s1 & 0xFFFF) < temp_v0);
    }
    temp_v0_4 = func_800821C0();
    if (temp_v0_4 != 0) {
        func_8008228C(temp_v0_4);
        if (func_80081A30() & 0xFF) {
            func_80083394(temp_v0_4);
            return;
        }
        func_80083F04(temp_v0_4);
    }
}
