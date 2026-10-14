#include "types.h"

typedef struct Unit Unit;

typedef struct UnitContact {
    s32 mode;
    u8 pad04[0xD];
    s8 value11;
    u8 pad12[2];
    Unit *target;
} UnitContact;

struct Unit {
    u8 pad00[4];
    u8 entityId;
    u8 pad05[0x93];
    s32 value98;
    UnitContact contact;
};

typedef struct EntityRecord {
    u8 pad000[0x1AC];
    u16 counter1AC;
} EntityRecord;

extern void func_800983E0(Unit *unit, s32 amount, u8 entityId, s32 arg3);
extern EntityRecord *get_entity_record(u8 index) __asm__("func_800A6688");

void resolve_unit_pair_contact(Unit *first, Unit *second) __asm__("func_800E4584");

void resolve_unit_pair_contact(Unit *first, Unit *second)
{
    EntityRecord *record;
    u8 entityId;
    UnitContact *contact = &second->contact;

    if (first->contact.mode == 8 && first->contact.target == second) {
        first->contact.value11 = 1;
    } else if (contact->mode == 8 && contact->target == first) {
        contact->value11 = 1;
    }

    if (first->value98 != 0) {
        func_800983E0(second, 10000, second->entityId, 0);
        entityId = second->entityId;
    } else if (second->value98 != 0) {
        func_800983E0(first, 10000, first->entityId, 0);
        entityId = first->entityId;
    } else {
        return;
    }

    record = get_entity_record(entityId);
    if (record->counter1AC < 10000) {
        record->counter1AC++;
    }
}
