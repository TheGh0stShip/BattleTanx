#include "types.h"

typedef struct RuntimeSlot48 {
    u8 pad00[0x20];
    s16 value;
    u8 pad22[0xE];
} RuntimeSlot48;

typedef struct RuntimeSlotTable {
    u8 pad00[0x40];
    RuntimeSlot48 *slots;
} RuntimeSlotTable;

void set_slot_halfword_20(RuntimeSlotTable *table, s16 index, u8 value)
{
    RuntimeSlot48 *slots;
    RuntimeSlot48 *slot;
    s32 offset;
    u32 stored_value;

    slots = table->slots;
    offset = index * sizeof(RuntimeSlot48);
    stored_value = value;
    slot = (RuntimeSlot48 *)((u8 *)slots + offset);
    slot->value = stored_value;
}
