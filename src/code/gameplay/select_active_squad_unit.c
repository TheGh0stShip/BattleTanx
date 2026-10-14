#include "types.h"

typedef struct SquadUnit {
    u8 value00;
    u8 value01;
    u8 value02;
    s8 value03;
    u8 pad04[0x10];
    u16 value14;
} SquadUnit;

typedef struct Squad {
    s16 ids[16];
    s16 value20;
    u8 pad22[0x184];
    u8 value1A6;
} Squad;

extern SquadUnit *get_unit(s16 id) __asm__("func_800A03B8");
extern s32 func_800A0218(SquadUnit *unit);
extern s32 func_800A0134(SquadUnit *unit);
extern void func_800E4344(SquadUnit *unit, s32 active);
extern s32 D_80135834;

SquadUnit *select_active_squad_unit(Squad *squad) __asm__("func_800A4500");

static inline SquadUnit *make_unit_active(Squad *squad, SquadUnit *unit, s16 *slot) {
    unit->value03 = 1;
    unit->value14 &= 0x7FFF;
    squad->value20 = *slot;
    if (squad->value1A6 == 0 && D_80135834 != 0) {
        func_800E4344(unit, 0);
    }
    return unit;
}

SquadUnit *select_active_squad_unit(Squad *squad) {
    SquadUnit *unit;
    s32 i;

    for (i = 0; i < 5; i++) {
        unit = get_unit(squad->ids[i]);
        if (unit->value01 & func_800A0218(unit)) {
            return make_unit_active(squad, unit, &squad->ids[i]);
        }
    }
    for (i = 0; i < 5; i++) {
        unit = get_unit(squad->ids[i]);
        if (unit->value01 != 0 && func_800A0134(unit) > 0) {
            return make_unit_active(squad, unit, &squad->ids[i]);
        }
    }
    return 0;
}
