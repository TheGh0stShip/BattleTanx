#include "types.h"
s32 integer_power(s32 base, s32 exponent) __asm__("func_80086340");
s32 integer_power(s32 base, s32 exponent)
{
    s32 result = 1;
    s32 i;
    for (i = 0; i < exponent; i++) result *= base;
    return result;
}
