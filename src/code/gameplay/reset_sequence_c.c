#include "types.h"

extern u8 gSequenceCIndex __asm__("D_80327D40");
extern u8 gSequenceCState __asm__("D_80327E30");

void reset_sequence_c(void) __asm__("func_800C0880");

void reset_sequence_c(void)
{
    gSequenceCIndex = 0;
    gSequenceCState = 0;
}
