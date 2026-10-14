#include "types.h"

extern void debug_pi_write_word(u32 address, u32 value) __asm__("func_80076068");
extern void debug_pi_write_byte(u32 address, u8 value) __asm__("func_80076390");

void debug_pi_write_bytes(u32 dest, u8 *source, u32 length) __asm__("func_80076408");

void debug_pi_write_bytes(u32 dest, u8 *source, u32 length)
{
    while (length != 0 && (dest & 3) != 0) {
        debug_pi_write_byte(dest++, *source++);
        length--;
    }
    while (length >= 4) {
        debug_pi_write_word(dest, (source[0] << 24) | (source[1] << 16) | (source[2] << 8) | source[3]);
        dest += 4;
        source += 4;
        length -= 4;
    }
    while (length != 0) {
        debug_pi_write_byte(dest++, *source++);
        length--;
    }
}
