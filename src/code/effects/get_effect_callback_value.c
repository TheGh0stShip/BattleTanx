#include "types.h"

extern u16 gEffectCallbackValue __asm__("D_802DF34A");

s32 get_effect_callback_value(s32 arg0, s32 arg1, s32 arg2, s32 *arg3)
    __asm__("func_800A66B0");

s32 get_effect_callback_value(s32 arg0, s32 arg1, s32 arg2, s32 *arg3)
{
    return (s32)gEffectCallbackValue;
}
