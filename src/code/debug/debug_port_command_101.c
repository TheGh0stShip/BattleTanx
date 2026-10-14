#include "types.h"

#ifndef NULL
#define NULL 0
#endif

s32 func_80076000();
s32 func_80076038(s32);
s32 func_80076BF0(s32, s32, s32, s32);

s32 debug_port_command_101(void) __asm__("func_80076CC8");

s32 debug_port_command_101(void) {
    s32 temp_s0;
    s32 temp_s0_2;

    temp_s0_2 = func_80076000();
    temp_s0 = func_80076BF0(0x101, 0, 0, 0);
    func_80076038(temp_s0_2);
    return temp_s0;
}
