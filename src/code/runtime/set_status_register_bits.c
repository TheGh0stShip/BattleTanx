#include "types.h"

extern u32 read_status_register(void) __asm__("func_800771F4");
extern void write_status_register(u32 value) __asm__("func_80077200");

void set_status_register_bits(u32 bits) __asm__("func_80076038");

void set_status_register_bits(u32 bits)
{
    write_status_register(read_status_register() | bits);
}
