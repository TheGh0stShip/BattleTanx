#include "types.h"

extern s32 disable_interrupt_bit0(void) __asm__("func_80076000");
extern void set_status_register_bits(s32 bits) __asm__("func_80076038");
extern s32 func_80076BF0(s32 command, s32 arg0, s32 arg1, s32 arg2);

s32 debug_port_command_707(s32 arg0, s32 arg1, s32 arg2) __asm__("func_80077028");

s32 debug_port_command_707(s32 arg0, s32 arg1, s32 arg2)
{
    s32 savedMask;
    s32 result;

    savedMask = disable_interrupt_bit0();
    result = func_80076BF0(0x707, arg0, arg1, arg2);
    set_status_register_bits(savedMask);
    return result;
}
