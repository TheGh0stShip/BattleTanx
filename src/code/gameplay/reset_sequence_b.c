#include "types.h"

extern u8 gSequenceBIndex __asm__("D_80327C30");
extern u8 gSequenceBState __asm__("D_80327D2C");

void reset_sequence_b(void) __asm__("func_800BD1F0");

void reset_sequence_b(void)
{
    gSequenceBIndex = 0xFF;
    gSequenceBState = 0;
}
