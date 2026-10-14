#include "types.h"

extern void debug_pi_write_word(u32 address, u32 value) __asm__("func_80076068");
extern u32 debug_pi_read_word(u32 address) __asm__("func_800760A0");
extern void debug_delay(s32 count) __asm__("func_800760DC");

void debug_port_copy_to_cart(void) __asm__("func_800767E4");

void debug_port_copy_to_cart(void)
{
    u32 source;
    u32 size;
    u32 i;

    source = debug_pi_read_word(0xB1FFFFF4) & 0xB1FFFFFC;
    size = debug_pi_read_word(0xB1FFFFF8) & 0x01FFFFFC;
    debug_pi_write_word(0xB1FFFFFC, 0);
    while (debug_pi_read_word(0xB0000010) == 0) {
        debug_delay(500);
    }
    for (i = 0; i < size / 4; i++) {
        debug_pi_write_word((source & 0xB07FFFFF) + i * 4, debug_pi_read_word(source + i * 4));
    }
    debug_delay(2000);
    debug_pi_write_word(0xB1FFFFF4, 0);
}
