#include "types.h"

typedef struct SelectorEntity {
    u8 pad00[0x20];
    s16 unitId;
    u8 pad22[0x3E];
    s32 value60;
} SelectorEntity;

typedef struct SelectorUnit {
    u8 pad00;
    u8 value01;
    u8 pad02[0x34E];
    u8 value350;
    u8 pad351[0x1B3];
    s32 value504;
} SelectorUnit;

extern SelectorEntity *get_entity_record(u16 index) __asm__("func_800A6688");
extern SelectorUnit *get_unit(s16 id) __asm__("func_800A03B8");
extern u8 gSelectedUnitIndex __asm__("D_8013589D");
extern u8 gSelectedUnitValue350 __asm__("D_8013589E");
extern u8 gSelectedUnitEnabled __asm__("D_8013589F");

void update_selected_unit_link(void) __asm__("func_800E51C0");

void update_selected_unit_link(void)
{
    SelectorEntity *entity = get_entity_record(0);
    u32 own;
    s32 fallback;
    SelectorUnit *unit;

    fallback = 0;
    unit = get_unit(entity->unitId);
    if (unit == 0) {
        own = 0;
    } else {
        own = unit->value504;
    }
    if (gSelectedUnitIndex < 20) {
        SelectorUnit *selected = get_unit(gSelectedUnitIndex);
        gSelectedUnitValue350 = selected->value350;
        if (selected->value01 != 0 && gSelectedUnitEnabled != 0) {
            entity->value60 = selected->value504;
        } else {
            fallback = 1;
        }
    } else {
        fallback = 1;
        gSelectedUnitValue350 = 0;
    }
    if (fallback && ((gSelectedUnitEnabled != 0) & (own != 0)) && entity->value60 != own) {
        entity->value60 = own;
    }
}
