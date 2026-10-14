#include "types.h"

extern u8 debug_pi_read_byte(u32 address) __asm__("func_80076124");
extern void debug_pi_write_byte(u32 address, u8 value) __asm__("func_80076390");

void debug_pi_copy_bytes(u32 dst, u32 src, u32 size) __asm__("func_800765C0");

void debug_pi_copy_bytes(u32 dst, u32 src, u32 size) {
    while (size--) {
        debug_pi_write_byte(dst++, debug_pi_read_byte(src++));
    }
}
