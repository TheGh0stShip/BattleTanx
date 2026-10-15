#include "types.h"

typedef struct SquadUnit {
    u8 value00;
    u8 value01;
    u8 value02;
    s8 value03;
    u8 pad04[0x10];
    union {
        s32 word;
        struct {
            u16 hi;
            u16 lo;
        } half;
    } value14;
} SquadUnit;

typedef struct Squad {
    s16 ids[16];
    s16 value20;
    u8 pad22[0x18];
    s16 value3A;
    u8 pad3C[0x16A];
    u8 value1A6;
    u8 pad1A7[0x161];
    u8 value308;
} Squad;

extern SquadUnit *get_unit(s16 id) __asm__("func_800A03B8");
extern void func_800E4344(SquadUnit *unit, s32 active);
extern s32 D_80135834;

static inline SquadUnit *make_unit_active(Squad *squad, SquadUnit *unit, s16 *slot) {
    unit->value03 = 1;
    unit->value14.half.hi &= 0x7FFF;
    squad->value20 = *slot;
    if (squad->value1A6 == 0 && D_80135834 != 0) {
        func_800E4344(unit, 0);
    }
    return unit;
}

SquadUnit *select_squad_unit_for_mode(Squad *squad, u8 mode) __asm__("func_800A4374");

SquadUnit *select_squad_unit_for_mode(Squad *squad, u8 mode) {
    SquadUnit *unit;
    s32 i;

    if (mode != 2) {
        for (i = 0; i < 5; i++) {
            unit = get_unit(squad->ids[i]);
            if (unit->value01 != 0 && !(unit->value14.word & 0x09000000)) {
                return make_unit_active(squad, unit, &squad->ids[i]);
            }
        }
    }
    for (i = 0; i < 5; i++) {
        unit = get_unit(squad->ids[i]);
        if (unit->value01 == 0) {
            continue;
        }
        if (unit->value14.half.hi & 0x100) {
            continue;
        }
        if (mode == 0 && (unit->value14.half.hi & 0x800)) {
            if (squad->value3A != 0 || squad->value308 != 0) {
                continue;
            }
        }
        if (mode == 2 && !(unit->value14.half.hi & 0x800)) {
            continue;
        }
        return make_unit_active(squad, unit, &squad->ids[i]);
    }
    return 0;
}
