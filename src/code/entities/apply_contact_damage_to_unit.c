#include "types.h"

typedef struct DamageUnit {
    u8 pad000[0x3E0];
    f32 value3E0;
    f32 value3E4;
} DamageUnit;

typedef struct DamageObject {
    u8 pad00[0xC];
    DamageUnit *unit;
} DamageObject;

typedef struct DamageEvent {
    u8 pad00[0x8];
    s32 amount;
    s32 source;
} DamageEvent;

extern void func_800983E0(DamageUnit *unit, s32 amount, s32 source, s32 arg3);

void apply_contact_damage_to_unit(DamageObject *object, s32 arg1, DamageEvent *event) __asm__("func_8009F100");

void apply_contact_damage_to_unit(DamageObject *object, s32 arg1, DamageEvent *event)
{
    DamageUnit *unit;

    unit = object->unit;
    func_800983E0(unit, event->amount, event->source, 0);
    unit->value3E0 += event->amount / 4;
    unit->value3E4 += event->amount / 4;
}
