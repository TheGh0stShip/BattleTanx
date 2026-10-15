#include "types.h"

typedef struct UnitSlot {
    u16 value;
    u16 assignment;
} UnitSlot;

extern u16 get_current_unit_group(void) __asm__("func_800E05A4");
extern UnitSlot *get_unit_slots(u16 group) __asm__("func_800E09B0");
extern u8 unit_assignment_is_active(u16 assignment) __asm__("func_800E19DC");

u16 select_available_current_group_slot(void) __asm__("func_800E0870");

u16 select_available_current_group_slot(void)
{
    u16 group;
    UnitSlot *slots;
    u16 selected;
    u16 i;

    group = get_current_unit_group();
    slots = get_unit_slots(group);
    selected = 0;
    for (i = 0; i < 3; i++) {
        UnitSlot *slot = &slots[i];

        if (slot->assignment != 0 && !unit_assignment_is_active(slot->assignment / 3)) {
            selected = i + group * 3;
            break;
        }
    }
    if (selected == 0) {
        selected = group * 3;
    }
    return selected;
}
