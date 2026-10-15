#include "types.h"

extern f32 D_80074B30;

void delay_with_saved_arguments(volatile s32 arg0, volatile s32 arg1,
                                volatile s32 arg2, volatile s32 arg3)
    __asm__("func_800EDADC");

void delay_with_saved_arguments(volatile s32 arg0, volatile s32 arg1,
                                volatile s32 arg2, volatile s32 arg3)
{
    volatile f32 value[3];
    s32 i;

    value[1] = D_80074B30;
    for (i = 3; i >= 0; i--) {
    }
}
