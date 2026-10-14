#include "types.h"

extern s32 gEntitySlotActive[] __asm__("D_8033AAC8");

void mark_entity_slot_active(s32 index) __asm__("func_800E4A18");

void mark_entity_slot_active(s32 index)
{
    gEntitySlotActive[index & 0xFFFF] = 1;
}
