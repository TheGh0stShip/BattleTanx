#include "types.h"

extern u32 debug_pi_read_word(u32 address) __asm__("func_800760A0");
extern u32 debug_pi_read_byte(u32 address) __asm__("func_80076124");
extern void debug_store_byte(u32 address, u8 value) __asm__("func_80076240");

void debug_pi_read_bytes(u32 source, u32 dest, u32 length) __asm__("func_8007627C");

void debug_pi_read_bytes(u32 source, u32 dest, u32 length)
{
    u32 word;

    while (length != 0 && (source & 3) != 0) {
        debug_store_byte(dest++, debug_pi_read_byte(source++));
        length--;
    }
    while (length >= 4) {
        word = debug_pi_read_word(source);
        debug_store_byte(dest++, word >> 24);
        debug_store_byte(dest++, word >> 16);
        debug_store_byte(dest++, word >> 8);
        debug_store_byte(dest++, word);
        source += 4;
        length -= 4;
    }
    while (length != 0) {
        debug_store_byte(dest++, debug_pi_read_byte(source++));
        length--;
    }
}
