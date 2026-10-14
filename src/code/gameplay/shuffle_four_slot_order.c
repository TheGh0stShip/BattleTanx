#include "types.h"

extern u32 next_random_u32(void) __asm__("func_800F38F4");
extern u8 gSlotOrder[4] __asm__("D_801260A0");
extern u8 gSlotRank[4] __asm__("D_801260A4");

void shuffle_four_slot_order(void) __asm__("func_800A30A8");

void shuffle_four_slot_order(void)
{
    gSlotOrder[0] = next_random_u32() & 3;
    do {
        gSlotOrder[1] = next_random_u32() & 3;
    } while (gSlotOrder[1] == gSlotOrder[0]);
    do {
        gSlotOrder[2] = next_random_u32() & 3;
    } while (gSlotOrder[2] == gSlotOrder[1] || gSlotOrder[2] == gSlotOrder[0]);
    do {
        gSlotOrder[3] = next_random_u32() & 3;
    } while (gSlotOrder[3] == gSlotOrder[1] || gSlotOrder[3] == gSlotOrder[0] || gSlotOrder[3] == gSlotOrder[2]);
    gSlotRank[gSlotOrder[0]] = 0;
    gSlotRank[gSlotOrder[1]] = 1;
    gSlotRank[gSlotOrder[2]] = 2;
    gSlotRank[gSlotOrder[3]] = 3;
}
