#include "types.h"

#ifndef NULL
#define NULL 0
#endif

s32 func_800771F4();
s32 func_80077200(s32);

s32 disable_interrupt_bit0(void) __asm__("func_80076000");

s32 disable_interrupt_bit0(void) {
    s32 temp_v0;

    temp_v0 = func_800771F4();
    func_80077200(temp_v0 & ~1);
    return temp_v0 & 1;
}
