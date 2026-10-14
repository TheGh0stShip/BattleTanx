#include "types.h"

void set_record_halfword_flags(s32 index, u16 mask) __asm__("func_80106C9C");

void set_record_halfword_flags(s32 index, u16 mask)
{
    u32 offset;

    offset = index * 0x28;
    *(u16 *)(offset + 0x803B8248) = *(u16 *)(offset + 0x803B8248) | mask;
}
