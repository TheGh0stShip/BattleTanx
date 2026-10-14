#include "types.h"

typedef struct SlotMarkerEffect {
    u8 pad00[0xC];
    s32 value0C;
    f32 pos[3];
    s16 value1C;
    u8 pad1E[0x2];
    s32 slot;
    u8 entityId;
    u8 flag25;
    u8 value26;
} SlotMarkerEffect;

typedef struct SlotMarkerEntry {
    SlotMarkerEffect *effect;
    u8 pad04[0x24];
} SlotMarkerEntry;

typedef struct MarkerEntity {
    u8 pad000[0x1BF];
    u8 value1BF;
} MarkerEntity;

extern SlotMarkerEffect *allocate_effect(s32 group, s32 kind, s32 size) __asm__("func_8008AD10");
extern MarkerEntity *get_entity_record(u16 index) __asm__("func_800A6688");
extern void clear_record_halfword_flags(s32 index, u16 flags) __asm__("func_80106CCC");
extern SlotMarkerEntry D_803B8250[];

s32 spawn_slot_marker_effect(s32 value, f32 *pos, s16 value1C, u8 entityId, s32 slot, u8 flag) __asm__("func_800A0400");

s32 spawn_slot_marker_effect(s32 value, f32 *pos, s16 value1C, u8 entityId, s32 slot, u8 flag)
{
    SlotMarkerEffect *effect = allocate_effect(0, 0x1A, 0x28);

    if (effect == 0) {
        return -1;
    }
    effect->value0C = value;
    effect->pos[0] = pos[0];
    effect->pos[1] = pos[1];
    effect->pos[2] = pos[2];
    effect->value1C = value1C;
    effect->flag25 = flag;
    effect->entityId = entityId;
    effect->value26 = get_entity_record(entityId)->value1BF;
    effect->slot = slot;
    D_803B8250[slot].effect = effect;
    if (flag) {
        clear_record_halfword_flags(slot, 0x94);
    }
    return 0;
}
