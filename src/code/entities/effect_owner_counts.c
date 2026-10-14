#include "types.h"

extern u8 D_802DF344[];

void increment_effect_owner_count(s32 owner) __asm__("func_800A6864");
void decrement_effect_owner_count(s32 owner) __asm__("func_800A6888");
u8 get_effect_owner_count(s32 owner) __asm__("func_800A68AC");

void increment_effect_owner_count(s32 owner)
{
    D_802DF344[owner]++;
}

void decrement_effect_owner_count(s32 owner)
{
    D_802DF344[owner]--;
}

u8 get_effect_owner_count(s32 owner)
{
    return D_802DF344[owner];
}
