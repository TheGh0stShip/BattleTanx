#include "types.h"

extern void debug_pi_write_word(u32 address, u32 value) __asm__("func_80076068");
extern void debug_pi_write_byte(u32 address, u8 value) __asm__("func_80076390");

void debug_pi_fill(u32 address, u8 value, u32 length) __asm__("func_800764F4");

void debug_pi_fill(u32 address, u8 value, u32 length) {
    u32 word;

    while (length != 0 && (address & 3) != 0) {
        debug_pi_write_byte(address++, value);
        length--;
    }
    if (length >= 4) {
        word = (value << 24) | (value << 16) | (value << 8) | value;
        do {
            debug_pi_write_word(address, word);
            length -= 4;
            address += 4;
        } while (length >= 4);
    }
    while (length != 0) {
        debug_pi_write_byte(address++, value);
        length--;
    }
}
