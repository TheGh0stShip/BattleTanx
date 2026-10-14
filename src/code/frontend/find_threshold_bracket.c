#include "types.h"

extern s32 D_80134FC0[];

s32 find_threshold_bracket(s32 value, s32 arg1, s32 arg2, s32 *exact, s32 *offset) __asm__("func_800D3AC4");

/* Returns the first index whose threshold exceeds value, with the offset from the previous threshold. */
s32 find_threshold_bracket(s32 value, s32 arg1, s32 arg2, s32 *exact, s32 *offset) {
    s32 i;

    for (i = 0; i < 8; i++) {
        if (value < D_80134FC0[i]) {
            *exact = value == D_80134FC0[i - 1];
            *offset = value - D_80134FC0[i - 1];
            return i;
        }
    }
    return 8;
}
