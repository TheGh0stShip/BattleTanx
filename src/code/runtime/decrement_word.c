#include "types.h"

void decrement_word(s32 *value) __asm__("func_800EA1EC");

void decrement_word(s32 *value)
{
    *value -= 1;
}
