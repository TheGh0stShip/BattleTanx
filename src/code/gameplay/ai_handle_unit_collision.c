#include "types.h"

typedef struct CollisionLink {
    s32 state;
    u8 pad04[0xD];
    u8 value11;
    u8 pad12[0x2];
    struct CollisionUnit *target;
} CollisionLink;

typedef struct CollisionUnit {
    u8 pad000[0x4];
    u8 entityId;
    u8 pad005[0x93];
    s32 value98;
    CollisionLink link;
    u8 pad0B4[0x29C];
    u8 mode;
    u8 timer;
} CollisionUnit;

typedef struct CollisionRecord {
    u8 pad000[0x1AC];
    u16 count;
    u8 team;
} CollisionRecord;

typedef struct CollisionContact {
    u8 pad00[0x8];
    s32 kind;
    CollisionUnit *unit;
} CollisionContact;

extern void func_800983E0(CollisionUnit *unit, s32 amount, s32 source, s32 arg3);
extern void func_800A2DC0(CollisionContact *contact);
extern CollisionRecord *get_entity_record(u16 index) __asm__("func_800A6688");
extern void ai_measure_relative_point(void *entity, f32 *point, s32 arg2, s32 *result, s32 arg4)
    __asm__("func_800E28DC");

static inline s32 unit_mode_is_one(CollisionUnit *unit)
{
    return unit->mode == 1;
}

static inline s32 unit_mode_is_two(CollisionUnit *unit)
{
    return unit->mode == 2;
}

void ai_handle_unit_collision(CollisionUnit *unit, CollisionContact *contact, s32 arg2, f32 *point)
    __asm__("func_800E4660");

void ai_handle_unit_collision(CollisionUnit *unit, CollisionContact *contact, s32 arg2, f32 *point)
{
    s32 result;
    CollisionUnit *other;
    u8 team;
    u8 otherTeam;
    CollisionRecord *record;
    u8 id;
    CollisionLink *link;

    if (unit_mode_is_one(unit) || contact == 0) {
        return;
    }
    if (contact->kind != 0) {
        if (contact->kind != 0x1B) {
            return;
        }
        func_800A2DC0(contact);
        goto measure;
    }
    other = contact->unit;
    team = get_entity_record(unit->entityId)->team;
    otherTeam = get_entity_record(other->entityId)->team;
    if (unit_mode_is_two(unit)) {
        if (unit_mode_is_two(other)) {
            if (team != otherTeam) {
                goto measure;
            }
            link = &other->link;
            if (unit->link.state == 8 && unit->link.target == other) {
                unit->link.value11 = 1;
            } else if (link->state == 8 && link->target == unit) {
                link->value11 = 1;
            }
            if (unit->value98 != 0) {
                func_800983E0(other, 0x2710, other->entityId, 0);
                id = other->entityId;
            } else if (other->value98 != 0) {
                func_800983E0(unit, 0x2710, unit->entityId, 0);
                id = unit->entityId;
            } else {
                goto measure;
            }
            record = get_entity_record(id);
            if (record->count < 0x2710) {
                record->count++;
            }
        } else {
            unit->timer = 0x3C;
        }
    } else if (unit_mode_is_two(other)) {
        other->timer = 0x3C;
    }
measure:
    ai_measure_relative_point(unit, point, 0, &result, 0);
}
