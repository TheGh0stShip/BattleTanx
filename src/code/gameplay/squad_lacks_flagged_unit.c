#include "types.h"

typedef struct SquadUnit {
    u8 pad00;
    u8 active;
    u8 pad02[0x96];
    s32 value98;
} SquadUnit;

typedef struct UnitSlotOwner {
    u8 pad00[0x1A];
    u16 entityId;
} UnitSlotOwner;

extern s32 get_entity_capacity(void) __asm__("func_8007AAB0");
extern s16 *get_linked_entity_ids(u16 id) __asm__("func_800A6688");
extern SquadUnit *get_unit(s16 id) __asm__("func_800A03B8");
extern f32 D_800747C8; /* 1.0f */
extern f32 D_800747CC; /* 1.0f */

static inline f32 squad_has_flagged_unit(UnitSlotOwner *owner) {
    u16 entityId = owner->entityId;
    s16 *ids;
    u16 i;
    f32 value = 0.0f;

    if (entityId >= get_entity_capacity()) {
        return value;
    }
    ids = get_linked_entity_ids(entityId);
    for (i = 0; i < 5; i++) {
        SquadUnit *unit = get_unit(ids[i]);
        if (unit->active != 0 && unit->value98 != 0) {
            value = D_800747C8;
            break;
        }
    }
    return value;
}

f32 squad_lacks_flagged_unit(UnitSlotOwner *owner) __asm__("func_800E885C");

f32 squad_lacks_flagged_unit(UnitSlotOwner *owner) {
    if (squad_has_flagged_unit(owner) > 0.0f) {
        return 0.0f;
    }
    return D_800747CC;
}
