#include "types.h"

extern u8 gRuntimeByteSetting __asm__("D_80125854");

s32 get_runtime_byte_setting(void) __asm__("func_80081A30");
void set_runtime_byte_setting(s32 value) __asm__("func_80081A40");

s32 get_runtime_byte_setting(void)
{
    return (s32)gRuntimeByteSetting;
}

void set_runtime_byte_setting(s32 value)
{
    gRuntimeByteSetting = value;
}
