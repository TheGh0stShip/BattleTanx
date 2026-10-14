#include "types.h"

extern u32 debug_pi_read_word(u32 address) __asm__("func_800760A0");

u8 debug_pi_read_byte(u32 address) __asm__("func_80076124");

u8 debug_pi_read_byte(u32 address)
{
    s32 shift;

    shift = (~address & 3) << 3;
    return (debug_pi_read_word(address & ~3U) >> shift) & 0xFF;
}
