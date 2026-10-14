#include "types.h"

extern u8 gSequenceDState __asm__("D_80327E50");

void reset_sequence_d(void) __asm__("func_800C3EF0");

void reset_sequence_d(void)
{
    gSequenceDState = 0;
}
