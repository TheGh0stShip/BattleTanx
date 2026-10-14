#include "types.h"

extern s32 D_80137904;
extern s32 D_8013790C[];

s32 get_runtime_slot_value(void) __asm__("func_800EC3F0");

s32 get_runtime_slot_value(void)
{
    return D_8013790C[D_80137904];
}
