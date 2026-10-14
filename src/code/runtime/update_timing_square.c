#include "types.h"

extern s32 D_80125858;
extern s32 D_801C9174;

void update_timing_square(void) __asm__("func_800862B4");

void update_timing_square(void)
{
    s32 value = D_80125858;

    if (value >= 1801) {
        D_80125858 = value - 100;
        D_801C9174 = (value - 100) * (value - 100);
    }
}
