#include "types.h"

typedef struct SessionSlot {
    u8 pad00[0x4];
    s32 mode;
    u8 pad08[0x4A];
    s16 value52;
    u16 value54;
    u8 pad56[0x2];
} SessionSlot;

typedef struct SlotSession {
    u8 pad000[0x568];
    SessionSlot *slots;
} SlotSession;

typedef struct SlotOwner {
    u8 pad00[0x20];
    s32 slot;
    u8 pad24[0xC];
    u16 value30;
} SlotOwner;

extern SlotSession *func_800821C0(void);

void set_active_slot_mode_1c(SlotOwner *owner) __asm__("func_800F01D0");

void set_active_slot_mode_1c(SlotOwner *owner)
{
    SessionSlot *slot = &func_800821C0()->slots[owner->slot];

    if (slot->value52 != -1) {
        u16 value = owner->value30;

        slot->mode = 0x1C;
        slot->value54 = value;
    }
}
