#include "types.h"

typedef struct SquadUnitOwner {
    u8 pad00[4];
    u8 squadIndex;
} SquadUnitOwner;

extern SquadUnitOwner *get_unit(s16 id) __asm__("func_800A03B8");

s32 find_unit_slot_in_squad(SquadUnitOwner *unit) __asm__("func_800E2640");

s32 find_unit_slot_in_squad(SquadUnitOwner *unit) {
    s16 i;
    s32 start;

    start = unit->squadIndex * 5;
    for (i = start; i < start + 5; i++) {
        if (unit == get_unit(i)) {
            return i;
        }
    }
    return 0xFF;
}
