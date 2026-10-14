#include "types.h"

extern u8 gSequenceAIndex __asm__("D_80327B50");
extern u8 gSequenceAState __asm__("D_80327C0F");

void reset_sequence_a(void) __asm__("func_800B9C80");

void reset_sequence_a(void)
{
    gSequenceAIndex = 0xFF;
    gSequenceAState = 0;
}
