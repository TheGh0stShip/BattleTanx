#include "types.h"

typedef struct LinkedUnit {
    u8 pad00;
    u8 active;
    u8 pad02[0x96];
    s32 value98;
} LinkedUnit;

extern s32 get_entity_capacity(void) __asm__("func_8007AAB0");
extern s16 *get_linked_entity_ids(u16 index) __asm__("func_800A6688");
extern LinkedUnit *get_unit(s16 id) __asm__("func_800A03B8");
extern f32 D_80074768;

static inline f32 linked_unit_active_weight(u16 index) {
    f32 result = 0.0f;
    s16 *ids;
    u16 i;
    LinkedUnit *unit;

    if (index >= get_entity_capacity()) {
        return result;
    }
    ids = get_linked_entity_ids(index);
    for (i = 0; i < 5; i++) {
        unit = get_unit(ids[i]);
        if (unit->active && unit->value98) {
            result = D_80074768;
            break;
        }
    }
    return result;
}

f32 ai_parameter_linked_unit_active(void) __asm__("func_800E8204");

f32 ai_parameter_linked_unit_active(void) {
    return linked_unit_active_weight(3);
}
