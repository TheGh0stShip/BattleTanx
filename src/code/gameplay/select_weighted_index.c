#include "types.h"

extern u8 gWeightTable[] __asm__("D_802D5BA0");
extern u8 gWeightTotal __asm__("D_802D5BB7");
extern u32 next_random_u32(void) __asm__("func_800F38F4");

s32 select_weighted_index(void) __asm__("func_80090F10");

s32 select_weighted_index(void)
{
    s32 value;
    s32 index;

    index = 0;
    value = next_random_u32() % gWeightTotal;
    while (value >= gWeightTable[index]) {
        value -= gWeightTable[index++];
    }
    return index;
}
