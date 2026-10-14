#include "types.h"

extern void spawn_effect(s32 type, s32 leftValue, s32 rightValue, s32 flags)
    __asm__("func_800A8EF8");

void spawn_symmetric_effect(s32 type, s32 value) __asm__("func_800968FC");

void spawn_symmetric_effect(s32 type, s32 value)
{
    spawn_effect(type, value, value, 0);
}
