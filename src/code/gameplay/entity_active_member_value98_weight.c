#include "types.h"

typedef struct EntityRecord {
    s16 members[5];
} EntityRecord;

typedef struct SquadUnit {
    u8 pad00;
    u8 active;
    u8 pad02[0x96];
    s32 value98;
} SquadUnit;

extern s32 get_entity_capacity(void) __asm__("func_8007AAB0");
extern EntityRecord *get_entity_record(u16 index) __asm__("func_800A6688");
extern SquadUnit *get_unit(s16 id) __asm__("func_800A03B8");
extern f32 D_80074728;

f32 entity_active_member_value98_weight(u16 index) __asm__("func_800E7804");

f32 entity_active_member_value98_weight(u16 index) {
    f32 result = 0.0f;
    EntityRecord *record;
    SquadUnit *unit;
    u16 i;

    if (index >= get_entity_capacity()) {
        return result;
    }
    record = get_entity_record(index);
    for (i = 0; i < 5; i++) {
        unit = get_unit(record->members[i]);
        if (unit->active != 0 && unit->value98 != 0) {
            result = D_80074728;
            break;
        }
    }
    return result;
}
