#include "types.h"

typedef struct ModelUnit {
    u8 pad00[0x18];
    s32 kind;
} ModelUnit;

typedef struct ModelEntity {
    u8 pad00[0x44];
    u16 mode;
    u8 pad46[0x2];
    u8 refresh[0x20];
} ModelEntity;

/* Indexed by [difficulty >= 3][unit kind]. */
extern s32 D_80126128[2][3];
extern s32 D_80126140[2][3];

extern s32 get_difficulty_level(void) __asm__("func_8007AAA0");
extern void advance_refresh_record(void *record, s32 value) __asm__("func_80078654");
extern void set_refresh_record_value1c(void *record, s32 value) __asm__("func_800786D4");

void advance_entity_unit_model(ModelEntity *entity, s32 unused, ModelUnit *unit) __asm__("func_800A42D0");

void advance_entity_unit_model(ModelEntity *entity, s32 unused, ModelUnit *unit)
{
    s32 *table;

    if (entity->mode == 1) {
        table = D_80126140[get_difficulty_level() >= 3];
    } else {
        table = D_80126128[get_difficulty_level() >= 3];
    }
    advance_refresh_record(entity->refresh, table[unit->kind]);
    set_refresh_record_value1c(entity->refresh, 2);
}
