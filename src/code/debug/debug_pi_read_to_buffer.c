#include "types.h"

extern u32 debug_pi_read_word(u32 address) __asm__("func_800760A0");
extern u8 debug_pi_read_byte(u32 address) __asm__("func_80076124");

void debug_pi_read_to_buffer(u32 source, u8 *dest, u32 length) __asm__("func_80076164");

void debug_pi_read_to_buffer(u32 source, u8 *dest, u32 length)
{
    u32 word;

    while (length != 0 && (source & 3) != 0) {
        *dest++ = debug_pi_read_byte(source++);
        length--;
    }
    while (length >= 4) {
        word = debug_pi_read_word(source);
        *dest++ = word >> 24;
        *dest++ = word >> 16;
        *dest++ = word >> 8;
        *dest++ = word;
        source += 4;
        length -= 4;
    }
    while (length != 0) {
        *dest++ = debug_pi_read_byte(source++);
        length--;
    }
}
