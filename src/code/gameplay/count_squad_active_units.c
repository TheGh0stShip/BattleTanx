#include "types.h"

typedef struct SquadUnit {
    u8 pad00;
    u8 active;
    u8 pad02[0x12];
    s32 flags;
} SquadUnit;

typedef struct UnitSquad {
    s16 unitIds[5];
    u8 pad0A[0x30];
    u16 activeCount;
} UnitSquad;

extern SquadUnit *get_unit(s16 id) __asm__("func_800A03B8");

void count_squad_active_units(UnitSquad *squad) __asm__("func_800A5CD0");

void count_squad_active_units(UnitSquad *squad) {
    s32 i;
    SquadUnit *unit;

    for (i = 0; i < 5; i++) {
        unit = get_unit(squad->unitIds[i]);
        if (unit->active != 0 && !(unit->flags & 0x09000000)) {
            squad->activeCount++;
        }
    }
}
