#include "types.h"

f32 ai_parameter_constant_zero(void) __asm__("func_800E7718");
f32 ai_parameter_constant_one(void) __asm__("func_800E7724");

f32 ai_parameter_constant_zero(void)
{
    return 0.0f;
}

f32 ai_parameter_constant_one(void)
{
    return 1.0f;
}
