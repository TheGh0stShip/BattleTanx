#include "types.h"

extern s32 gEffectResultValue __asm__("D_802C13F0");

void set_effect_result_value(s32 value) __asm__("func_8008C2DC");

void set_effect_result_value(s32 value)
{
    gEffectResultValue = value;
}
