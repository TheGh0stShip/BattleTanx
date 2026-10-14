#include "types.h"

typedef struct Unit {
    u8 pad00[0x24];
    f32 value24;
    u8 pad28[0x4];
    f32 value2C;
    u8 pad30[0x4D4];
    s32 value504;
} Unit;

typedef struct ContactHit {
    u8 pad00[0x8];
    s32 value08;
    Unit *value0C;
} ContactHit;

extern s32 get_owner_class(Unit *unit) __asm__("func_8009FBE4");
extern s32 func_8010874C(f32 *pos, s32 mode, s32 count, ContactHit **out, s32 arg4);

s32 unit_probe_hit_not_same_class(Unit *unit, s32 mode) __asm__("func_800E2110");

s32 unit_probe_hit_not_same_class(Unit *unit, s32 mode) {
    f32 pos[2];
    ContactHit *hits[6];
    s32 cls;

    if (mode == 0) {
        goto none;
    }
    if (unit == 0) {
        goto none;
    }
    pos[0] = unit->value2C;
    pos[1] = unit->value24;
    if (func_8010874C(pos, mode, 4, hits, unit->value504) == 0) {
        return 1;
    }
    if ((u32)hits[0] < 4) {
        return 1;
    }
    if (hits[0]->value08 != 0) {
        return 1;
    }
    cls = get_owner_class(hits[0]->value0C);
    if ((u8)cls != (u8)get_owner_class(unit)) {
        return 1;
    }
none:
    return 0;
}
