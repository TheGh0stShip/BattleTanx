#include "types.h"

typedef struct ModelUnit {
    u8 pad000[0x1];
    u8 inUse;
    u8 pad002[0x16];
    s32 kind;
    u8 pad01C[0x4E8];
    s32 value504;
} ModelUnit;

typedef struct ModelEntity {
    u8 pad00[0x20];
    s16 unitId;
    u8 pad22[0x22];
    u16 mode;
    u8 pad46[0x2];
    u8 refresh[0x20];
} ModelEntity;

/* Indexed by [difficulty >= 3][unit kind]. */
extern s32 D_80126128[2][3];
extern s32 D_80126140[2][3];

extern ModelUnit *get_unit(s16 id) __asm__("func_800A03B8");
extern s32 get_difficulty_level(void) __asm__("func_8007AAA0");
extern void set_refresh_record_value18(void *record, s32 value) __asm__("func_80078634");
extern void advance_refresh_record_mode_64(void *record, s32 value) __asm__("func_80078680");

void refresh_entity_unit_model(ModelEntity *entity) __asm__("func_800A3D30");

void refresh_entity_unit_model(ModelEntity *entity)
{
    ModelUnit *unit;
    s32 *table;

    unit = get_unit(entity->unitId);
    if (unit->inUse == 0) {
        return;
    }
    if (entity->mode == 1) {
        table = D_80126140[get_difficulty_level() >= 3];
    } else {
        table = D_80126128[get_difficulty_level() >= 3];
    }
    advance_refresh_record_mode_64(entity->refresh, table[unit->kind]);
    set_refresh_record_value18(entity->refresh, unit->value504);
}
