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
    u8 pad18[0x3E4];
    f32 value3FC;
    f32 value400;
    u8 pad404[0x100];
    s32 value504;
} SquadUnit;

typedef struct Squad {
    s16 ids[16];
    s16 value20;
    u8 pad22[0x184];
    u8 value1A6;
    u8 pad1A7[0x5D];
    u8 value204;
} Squad;

extern SquadUnit *get_unit(s16 id) __asm__("func_800A03B8");
extern void func_80097B04(SquadUnit *unit);
extern void func_800A4E40(Squad *squad, s32 value);
extern void func_800E4344(SquadUnit *unit, s32 active);
extern s32 D_80135834;

s32 cycle_active_squad_unit(Squad *squad) __asm__("func_800A4610");

s32 cycle_active_squad_unit(Squad *squad) {
    s32 current = -1;
    s32 i;

    for (i = 0; i < 5; i++) {
        if (squad->ids[i] == squad->value20) {
            current = i;
        }
    }
    if (current != -1) {
        for (i = 1; i < 5; i++) {
            s16 *slot;
            SquadUnit *unit;

            slot = (s16 *)((current + i) % 5 * 2 + (s32)squad);
            unit = get_unit(*slot);
            if (unit->value01 != 0 && (unit->value14.word & 0x09000000) == 0x08000000) {
                SquadUnit *previous = get_unit(squad->value20);

                previous->value03 = 0;
                previous->value14.half.hi |= 8;
                func_80097B04(previous);
                unit->value03 = 1;
                unit->value14.half.hi &= 0x7FFF;
                squad->value20 = *slot;
                if (squad->value1A6 == 0) {
                    if (D_80135834 != 0) {
                        func_800E4344(previous, 1);
                        func_800E4344(unit, 0);
                    }
                    if (squad->value204 == 0 && !(unit->value14.half.hi & 4)) {
                        unit->value3FC = unit->value400;
                    }
                    func_800A4E40(squad, unit->value504);
                }
                return 0;
            }
        }
    }
    return -1;
}
