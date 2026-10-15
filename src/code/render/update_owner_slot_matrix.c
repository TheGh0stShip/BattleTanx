#include "types.h"

typedef struct RenderSlot {
    u8 pad00[0x8];
    u8 matrix[0x40];
    u8 pad48[0xA];
    s16 entryIndex;
    s16 displayValue;
    u8 pad56[0x2];
} RenderSlot;

typedef struct RenderEntry {
    u16 value;
    u16 baseDisplayValue;
} RenderEntry;

typedef struct RenderSession {
    u8 pad000[0x568];
    RenderSlot *slots;
    RenderEntry *entries;
} RenderSession;

typedef struct RenderOwner {
    u8 pad00[0xC];
    s32 z;
    s32 x;
    u8 pad14[0x2];
    u16 heading;
    u8 pad18[0x8];
    s32 slotIndex;
    u8 pad24[0x9];
    u8 flags;
} RenderOwner;

extern RenderSession *get_render_session(void) __asm__("func_800821C0");
extern void matrix_identity(f32 matrix[4][4]) __asm__("func_800A7650");
extern void matrix_set_transform(f32 matrix[4][4], s32 x, s32 z, u16 heading)
    __asm__("func_800A76BC");
extern void guMtxF2L(f32 matrix[4][4], void *output) __asm__("func_801146A0");

void update_owner_slot_matrix(RenderOwner *owner) __asm__("func_800EF2D0");

void update_owner_slot_matrix(RenderOwner *owner)
{
    s16 displayValue;
    f32 matrix[4][4];
    RenderSession *session = get_render_session();
    RenderSlot *slot;
    s16 entryIndex;

    slot = &session->slots[owner->slotIndex];
    entryIndex = slot->entryIndex;
    if (entryIndex != -1) {
        u16 baseDisplayValue;
        u8 flags = owner->flags;

        baseDisplayValue = session->entries[entryIndex].baseDisplayValue;
        if (flags & 1) {
            displayValue = baseDisplayValue + 3;
        } else {
            displayValue = baseDisplayValue + 1;
        }
        slot->displayValue = displayValue;
        matrix_identity(matrix);
        matrix_set_transform(matrix, owner->x, owner->z, owner->heading);
        guMtxF2L(matrix, slot->matrix);
    }
}
