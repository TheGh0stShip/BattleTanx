#include "types.h"

typedef struct ClearUnit {
    u8 pad00;
    u8 active;
    u8 pad02[0x12];
    u16 flags;
    u8 pad16[0x330];
    u16 slot;
} ClearUnit;

typedef struct ClearGroup {
    u8 pad00[8];
    s16 unitIds[15];
    u16 count;
} ClearGroup;

extern ClearUnit *get_unit(s16 id) __asm__("func_800A03B8");
extern s32 func_800E3470(ClearUnit *unit);

void clear_group_unit_slots(u8 *slots, ClearUnit *skip, ClearGroup *group) __asm__("func_800DEC5C");

void clear_group_unit_slots(u8 *slots, ClearUnit *skip, ClearGroup *group) {
    s32 i;
    ClearUnit *unit;

    if (group == 0) {
        return;
    }
    for (i = 0; i < group->count; i++) {
        unit = get_unit(group->unitIds[i]);
        if (unit->active) {
            if (unit != skip) {
                if (!(unit->flags & 4)) {
                    if (func_800E3470(unit) == 0) {
                        slots[unit->slot] = 0;
                    }
                }
            }
        }
    }
}
