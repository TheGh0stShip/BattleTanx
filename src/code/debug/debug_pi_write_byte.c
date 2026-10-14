#include "types.h"

extern void debug_pi_write_word(u32 address, u32 value) __asm__("func_80076068");
extern u32 debug_pi_read_word(u32 address) __asm__("func_800760A0");

void debug_pi_write_byte(u32 address, u8 value) __asm__("func_80076390");

void debug_pi_write_byte(u32 address, u8 value)
{
    s32 shift = (~address & 3) * 8;

    address &= ~3;
    debug_pi_write_word(address, (debug_pi_read_word(address) & ~(0xFF << shift)) | ((u32)value << shift));
}
