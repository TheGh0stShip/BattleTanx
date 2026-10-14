#include "types.h"

typedef struct SlotEntry {
    u8 pad00[0xC8];
    u8 valueC8;
    u8 padC9[3];
} SlotEntry;

typedef struct SlotOwner {
    u8 pad00[0x16];
    u16 value16;
    u8 pad18[0xB];
    u8 flags23;
} SlotOwner;

extern s32 *get_game_mode(void) __asm__("func_8007AAF4");
extern u8 gSlotOrder[4] __asm__("D_801260A0");

s32 owner_slot_entry_enabled(SlotOwner *owner, SlotEntry *entries) __asm__("func_80096FC8");

s32 owner_slot_entry_enabled(SlotOwner *owner, SlotEntry *entries) {
    SlotEntry *entry = (SlotEntry *)((u8 *)entries + gSlotOrder[owner->value16] * 0x14);

    if (entry->valueC8 != 0 && !(owner->flags23 & 2)) {
        if (*get_game_mode() != 9) {
            return 1;
        }
    }
    return 0;
}
