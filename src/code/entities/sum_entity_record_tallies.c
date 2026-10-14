#include "types.h"

typedef struct EntityRecord {
    u8 pad000[0x22];
    u8 value22;
    u8 pad023[0x1E5];
    s32 value208;
} EntityRecord;

extern s32 get_entity_capacity(void) __asm__("func_8007AAB0");
extern EntityRecord *get_entity_record(u16 index) __asm__("func_800A6688");

s32 sum_entity_record_tallies(void) __asm__("func_800A5D5C");

s32 sum_entity_record_tallies(void)
{
    s32 count = get_entity_capacity();
    s32 total = 0;
    u16 i;

    for (i = 1; i < count; i++) {
        EntityRecord *record = get_entity_record(i);

        total += record->value22;
        total += record->value208;
    }
    return total;
}
