#include "types.h"

void clear_word(u32 *value) __asm__("func_800EA1B0");

void clear_word(u32 *value)
{
    *value = 0;
}
