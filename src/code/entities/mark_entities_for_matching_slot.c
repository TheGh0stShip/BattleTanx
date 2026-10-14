#include "types.h"

typedef struct EntityRecord {
    u8 pad00[0x10];
    s32 value10;
    u8 pad14[0x19A];
    u8 value1AE;
    u8 pad1AF[0x199];
} EntityRecord;

extern s32 get_entity_capacity(void) __asm__("func_8007AAB0");
extern EntityRecord D_802DE620[];
extern u8 D_802DF340;
extern u8 D_802DF344[];

s32 mark_entities_for_matching_slot(void) __asm__("func_800A6798");

static inline EntityRecord *get_entity_record(u16 index) {
    return &D_802DE620[index];
}

s32 mark_entities_for_matching_slot(void) {
    s32 slot;
    s32 count;
    u16 i;
    EntityRecord *record;

    for (slot = 0; slot < 4; slot++) {
        if (D_802DF344[slot] == D_802DF340) {
            count = get_entity_capacity();
            for (i = 0; i < count; i++) {
                record = get_entity_record(i);
                if (record->value1AE == slot) {
                    record->value10 = 2;
                } else {
                    record->value10 = 0;
                }
            }
            return slot;
        }
    }
    return -1;
}
