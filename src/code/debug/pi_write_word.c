#include "types.h"

void debug_pi_write_word(u32 *address, u32 value)
{
    while (*(volatile u32 *)0xA4600010 & 3) {
    }
    *address = value;
}
