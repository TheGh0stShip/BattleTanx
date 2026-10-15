#include "types.h"

typedef struct TrackedObject {
    u8 pad00[8];
    s32 kind;
    u8 pad0C[0x22];
    u16 owner;
} TrackedObject;

typedef struct Unit {
    u8 value00;
    u8 value01;
    u8 pad02[0x34A];
    TrackedObject *tracked;
    u8 pad350[8];
    u8 tracking;
    u8 pad359[0xB];
    s32 trackStart;
} Unit;

extern Unit *get_unit(s16 id) __asm__("func_800A03B8");
extern void func_800E986C(Unit *unit, s32 flags, f32 scale);
extern s32 func_8007B1DC(void);

void update_unit_tracked_kind1b(void) __asm__("func_800E5AB0");

void update_unit_tracked_kind1b(void) {
    s16 i;
    Unit *unit;
    TrackedObject *object;
    s16 match;

    for (i = 0; i < 20; i++) {
        unit = get_unit(i);
        if (unit->value01 == 0) {
            continue;
        }
        if (unit->tracked == 0 || unit->tracked->kind != 0x1B) {
            object = 0;
        } else {
            object = unit->tracked;
        }
        match = 0;
        if (object != 0) {
            match = object->owner == i;
        }
        if (match == unit->tracking) {
            continue;
        }
        if (match) {
            func_800E986C(unit, 0x1002, 1.0f);
            unit->trackStart = func_8007B1DC();
            unit->tracking = 1;
        } else {
            unit->tracked = 0;
            unit->tracking = 0;
        }
    }
}
