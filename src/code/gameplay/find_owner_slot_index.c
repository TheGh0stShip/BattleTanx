#include "types.h"

typedef struct OwnerSlot {
    s32 id;
    u8 pad04[0xC];
} OwnerSlot;

typedef struct OwnerSlotTable {
    u8 pad0000[0x936C];
    s32 count;
    OwnerSlot slots[1];
} OwnerSlotTable;

typedef struct SlotOwner {
    u8 pad00[0x28];
    OwnerSlotTable *table;
} SlotOwner;

s32 find_owner_slot_index(SlotOwner *owner, s32 id) __asm__("func_80088004");

s32 find_owner_slot_index(SlotOwner *owner, s32 id) {
    OwnerSlotTable *table = owner->table;
    s32 i;

    for (i = 0; i < table->count; i++) {
        if (table->slots[i].id == id) {
            return i;
        }
    }
    return 0;
}
