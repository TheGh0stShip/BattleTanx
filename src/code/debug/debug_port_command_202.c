#include "types.h"

#ifndef NULL
#define NULL 0
#endif

s32 func_80076000();
s32 func_80076038(s32);
s32 func_80076408(s32, s32, s32);
s32 func_80076BF0(s32, s32, s32, s32);
s32 func_80076CA8(s32);

s32 debug_port_command_202(s32 arg0, s32 arg1) __asm__("func_80076D14");

s32 debug_port_command_202(s32 arg0, s32 arg1) {
    s32 temp_s2;
    s32 temp_v0;
    s32 var_s0;

    temp_s2 = func_80076000();
    temp_v0 = func_80076CA8(arg0);
    func_80076408(0xB1FF0000, arg0, temp_v0);
    var_s0 = func_80076BF0(0x202, temp_v0, arg1, 0);
    if (var_s0 & 0x8000) {
        var_s0 |= 0xFFFF0000;
    }
    func_80076038(temp_s2);
    return var_s0;
}
