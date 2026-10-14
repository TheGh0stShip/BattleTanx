#include "types.h"

typedef struct RuntimeSlot48 {
    u8 pad00[0x28];
    s32 value;
    u8 pad2C[4];
} RuntimeSlot48;

typedef struct RuntimeSlotOwner {
    u8 pad00[0x3C];
    s32 current;
    RuntimeSlot48 *slots;
} RuntimeSlotOwner;

s32 get_current_slot_value_28(RuntimeSlotOwner *owner)
{
    RuntimeSlot48 *slots;

    slots = owner->slots;
    return ((RuntimeSlot48 *)(owner->current * sizeof(RuntimeSlot48) + (u8 *)slots))->value;
}
