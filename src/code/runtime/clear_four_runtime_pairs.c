#include "types.h"

extern u8 D_801260A0[];
extern u8 D_801260A4[];

void clear_four_runtime_pairs(void) __asm__("func_800A3070");

void clear_four_runtime_pairs(void)
{
    register s32 i __asm__("$3") = 0;
    register s32 value __asm__("$2");

    __asm__ volatile("" : "=r"(i) : "0"(i));
    value = i;

loop:
    D_801260A4[i] = value;
    D_801260A0[i] = value;
    i++;
    value = i < 4;
    if (value != 0) {
        value = i;
        goto loop;
    }
}
