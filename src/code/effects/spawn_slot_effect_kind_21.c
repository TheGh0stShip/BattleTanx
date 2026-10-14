#include "types.h"

typedef struct SlotRecord {
    u8 pad00[0x54];
    u16 value54;
    u8 pad56[0x2];
} SlotRecord;

typedef struct SlotSession {
    u8 pad000[0x568];
    SlotRecord *slots;
} SlotSession;

typedef struct SlotEffect21 {
    u8 pad00[0xC];
    s8 value0C;
    u8 pad0D[0x3];
    f32 y;
    f32 x;
    u16 id;
    u8 pad1A[0x2];
    s32 handle;
    s32 slot;
    s32 value24;
    u8 pad28[0x4];
    u16 value2C;
    s16 value2E;
    s16 value30;
    s16 value32;
} SlotEffect21;

extern SlotEffect21 *allocate_effect(s32 group, s32 kind, s32 size) __asm__("func_8008AD10");
extern SlotSession *get_spawn_session(void) __asm__("func_800821C0");
extern s32 create_effect_motion(SlotEffect21 *effect, s32 x, s32 y, s32 minX, s32 maxX, s32 minY, s32 maxY,
                                s32 mode, s32 flags) __asm__("func_80106D18");

s32 spawn_slot_effect_kind_21(f32 x, f32 y, s32 slot, u16 id, s32 minX, s32 maxX, s32 minY, s32 maxY)
    __asm__("func_800F05F4");

s32 spawn_slot_effect_kind_21(f32 x, f32 y, s32 slot, u16 id, s32 minX, s32 maxX, s32 minY, s32 maxY) {
    SlotEffect21 *effect;
    SlotSession *session;

    effect = allocate_effect(0, 0x21, 0x38);
    if (effect == 0) {
        return -1;
    }
    session = get_spawn_session();
    effect->slot = slot;
    effect->value2C = session->slots[slot].value54;
    effect->value30 = session->slots[slot].value54 + 1;
    effect->value2E = session->slots[slot].value54 + 2;
    effect->x = x;
    effect->y = y;
    effect->value32 = 0;
    effect->id = id;
    effect->value0C = 0;
    effect->value24 = 10;
    effect->handle = create_effect_motion(effect, (s32)x, (s32)y, minX, maxX, minY, maxY, 0x56, id);
    return 0;
}
