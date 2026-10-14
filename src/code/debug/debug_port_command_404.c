#include "types.h"

#ifndef NULL
#define NULL 0
#endif

s32 func_80076000();
s32 func_80076038(s32);
s32 func_80076BF0(s32, s32, s32, s32);

s32 debug_port_command_404(s32 arg0) __asm__("func_80076E34");

s32 debug_port_command_404(s32 arg0) {
    s32 temp_s1;
    s32 var_s0;

    temp_s1 = func_80076000();
    var_s0 = func_80076BF0(0x404, arg0, 0, 0);
    if (var_s0 & 0x8000) {
        var_s0 |= 0xFFFF0000;
    }
    func_80076038(temp_s1);
    return var_s0;
}
