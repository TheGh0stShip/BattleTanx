#include "types.h"

typedef struct ModelUnit {
    u8 pad00[0x18];
    s32 kind;
} ModelUnit;

typedef struct ModelOwnerState {
    u8 pad00[0x8];
    s32 state;
    ModelUnit *unit;
} ModelOwnerState;

typedef struct ModelEntity {
    u8 pad00[0x44];
    u16 mode;
    u8 pad46[0x2];
    u8 refresh[0xA4];
    ModelOwnerState *owner;
} ModelEntity;

extern s32 D_80126128[2][3];
extern s32 D_80126140[2][3];
extern u8 D_801256C0[];
extern u8 D_801256D8[];

extern s32 get_difficulty_level(void) __asm__("func_8007AAA0");
extern void advance_refresh_record(void *record, s32 value) __asm__("func_80078654");
extern void set_refresh_record_value1c(void *record, s32 value) __asm__("func_800786D4");
extern void set_refresh_record_previous(void *record, void *value) __asm__("func_800786B0");

void refresh_entity_owner_model(ModelEntity *entity) __asm__("func_800A4D58");

void refresh_entity_owner_model(ModelEntity *entity)
{
    ModelUnit *unit;
    s32 *table;

    switch (entity->owner->state) {
    case 0:
        unit = entity->owner->unit;
        if (entity->mode == 1) {
            table = D_80126140[get_difficulty_level() >= 3];
        } else {
            table = D_80126128[get_difficulty_level() >= 3];
        }
        advance_refresh_record(entity->refresh, table[unit->kind]);
        set_refresh_record_value1c(entity->refresh, 2);
        set_refresh_record_previous(entity->refresh, D_801256D8);
        break;
    case 7:
        advance_refresh_record(entity->refresh, (s32)D_801256C0);
        break;
    }
}
