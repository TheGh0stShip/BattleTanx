#include "types.h"

u32 debug_pi_read_word(volatile u32 *address)
{
    while (*(volatile u32 *)0xA4600010 & 3) {
    }
    return *address;
}
