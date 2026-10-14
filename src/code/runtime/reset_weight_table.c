#include "types.h"

extern u8 gWeightTable[] __asm__("D_802D5BA0");
extern u8 gWeightTotal __asm__("D_802D5BB7");
extern void clear_bytes(s32 address, s32 count) __asm__("func_80110C00");

void reset_weight_table(void) __asm__("func_80090EE0");

void reset_weight_table(void)
{
    clear_bytes((s32)gWeightTable, 0x17);
    gWeightTotal = 0;
}
