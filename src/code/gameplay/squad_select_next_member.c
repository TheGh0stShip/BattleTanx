#include "types.h"

typedef struct {
    u8 pad000;
    u8 active;
    u8 pad002;
    u8 selected;
    u8 pad004[0x10];
    union {
        s32 word;
        u16 flags;
    } state;
    u8 pad018[0x3E4];
    f32 value3FC;
    f32 value400;
    u8 pad404[0x100];
    s32 value504;
} SquadUnit;

typedef struct {
    s16 members[16];
    s16 current;
    u8 pad022[0x184];
    u8 value1A6;
    u8 pad1A7[0x5D];
    u8 value204;
} Squad;

extern SquadUnit *get_unit(s16 id) __asm__("func_800A03B8");
extern void stop_entity_sound_handles(SquadUnit *unit) __asm__("func_80097B04");
extern void func_800A4E40(Squad *squad, s32 arg1);
extern void func_800E4344(SquadUnit *unit, s32 arg1);
extern void *gObjectRecordTable __asm__("D_80135834");

s32 squad_select_next_member(Squad *squad) __asm__("func_800A47AC");

s32 squad_select_next_member(Squad *squad) {
    SquadUnit *unit;
    SquadUnit *previous;
    s16 *slot;
    s32 currentIndex;
    s32 i;

    currentIndex = -1;
    for (i = 0; i < 5; i++) {
        if (squad->members[i] == squad->current) {
            currentIndex = i;
        }
    }
    if (currentIndex == -1) {
        return -1;
    }
    for (i = 1; i < 5; i++) {
        slot = (s16 *)(((currentIndex + i) % 5) * 2 + (s32)squad);
        unit = get_unit(*slot);
        if (unit->active != 0 && (unit->state.word & 0x1080000) == 0x80000) {
            previous = get_unit(squad->current);
            previous->selected = 0;
            stop_entity_sound_handles(previous);
            unit->selected = 1;
            unit->state.flags &= 0x7FF7;
            squad->current = *slot;
            if (squad->value1A6 != 0) {
                return 0;
            }
            if (gObjectRecordTable != 0) {
                func_800E4344(previous, 1);
                func_800E4344(unit, 0);
            }
            if (squad->value204 == 0 && !(unit->state.flags & 4)) {
                unit->value3FC = unit->value400;
            }
            func_800A4E40(squad, unit->value504);
            return 0;
        }
    }
    for (i = 1; i < 5; i++) {
        slot = (s16 *)(((currentIndex + i) % 5) * 2 + (s32)squad);
        unit = get_unit(*slot);
        if (unit->active != 0 && !(unit->state.flags & 0x100)) {
            previous = get_unit(squad->current);
            previous->selected = 0;
            stop_entity_sound_handles(previous);
            unit->selected = 1;
            unit->state.flags &= 0x7FF7;
            squad->current = *slot;
            if (squad->value1A6 != 0) {
                return 0;
            }
            if (gObjectRecordTable != 0) {
                func_800E4344(previous, 1);
                func_800E4344(unit, 0);
                if (squad->value204 == 0 && !(unit->state.flags & 4)) {
                    unit->value3FC = unit->value400;
                }
            }
            func_800A4E40(squad, unit->value504);
            return 0;
        }
    }
    return -1;
}
