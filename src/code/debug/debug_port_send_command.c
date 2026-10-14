#include "types.h"

extern void debug_pi_write_word(u32 address, u32 value) __asm__("func_80076068");
extern u32 debug_pi_read_word(u32 address) __asm__("func_800760A0");
extern void debug_delay(s32 count) __asm__("func_800760DC");

u32 debug_port_send_command(u32 command, u32 arg1, u32 arg2, u32 arg3) __asm__("func_80076BF0");

u32 debug_port_send_command(u32 command, u32 arg1, u32 arg2, u32 arg3) {
    debug_pi_write_word(0xB1FFFFE4, arg1);
    debug_pi_write_word(0xB1FFFFE8, arg2);
    debug_pi_write_word(0xB1FFFFEC, arg3);
    debug_pi_write_word(0xB1FFFFE0, command);
    do {
        debug_delay(1000);
        if (debug_pi_read_word(0xB1FFFFF0) != 0) {
            __asm__("break 1");
        }
    } while (debug_pi_read_word(0xB1FFFFE0) != 0);
    return debug_pi_read_word(0xB1FFFFDC);
}
