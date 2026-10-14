#include "types.h"

typedef struct IdOccurrence {
    s32 id;
    s32 value;
    s32 pad08;
    s32 count;
} IdOccurrence;

typedef struct IdOccurrenceTable {
    u8 pad0000[0xA374];
    s32 count;
    IdOccurrence entries[0x708];
} IdOccurrenceTable;

typedef struct IdOccurrenceOwner {
    u8 pad00[0x28];
    IdOccurrenceTable *table;
} IdOccurrenceOwner;

s32 record_id_occurrence(IdOccurrenceOwner *owner, s32 id, s32 value, s32 repeat) __asm__("func_80087054");

/* Bumps an existing entry for id, or appends one (count 1 or 2); returns -1 when the table is full. */
s32 record_id_occurrence(IdOccurrenceOwner *owner, s32 id, s32 value, s32 repeat)
{
    IdOccurrenceTable *table = owner->table;
    s32 i;

    for (i = 0; i < table->count; i++) {
        if (table->entries[i].id == id) {
            if (repeat != 0) {
                table->entries[i].count++;
            }
            return 0;
        }
    }
    if (table->count == 0x708) {
        return -1;
    }
    table->entries[table->count].count = repeat ? 2 : 1;
    table->entries[table->count].id = id;
    table->entries[table->count++].value = value;
    return 0;
}
