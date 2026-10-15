#include "types.h"

typedef struct RefEntry {
    s32 key;
    s32 value;
    s32 pad08;
    s32 refCount;
} RefEntry;

typedef struct IdOccurrence {
    s32 id;
    s32 value;
    s32 pad08;
    s32 count;
} IdOccurrence;

typedef struct ResourceSlot {
    s32 state;
    s32 pad04;
} ResourceSlot;

typedef struct ResourceRecord {
    s32 key;
    u8 pad04[2];
    u16 value;
    s32 id;
    s32 idValue;
} ResourceRecord;

typedef struct RefTable {
    u8 pad0000[0x936C];
    s32 count;
    RefEntry entries[256];
} RefTable;

typedef struct IdOccurrenceTable {
    u8 pad0000[0xA374];
    s32 count;
    IdOccurrence entries[0x708];
} IdOccurrenceTable;

typedef struct SlotTable {
    u8 pad0000[0x22F0];
    ResourceSlot slots[3600];
} SlotTable;

typedef struct Owner {
    u8 pad00[0x18];
    ResourceRecord *records;
    u8 pad1C[0xC];
    void *table;
} Owner;

static inline s32 ref_table_add_key(Owner *owner, s32 key, s32 value, s32 addRef) {
    RefTable *table = owner->table;
    s32 i;

    for (i = 0; i < table->count; i++) {
        if (table->entries[i].key == key) {
            if (addRef != 0) {
                table->entries[i].refCount++;
            }
            return 0;
        }
    }
    if (table->count == 256) {
        return -1;
    }
    table->entries[table->count].refCount = addRef ? 2 : 1;
    table->entries[table->count].key = key;
    table->entries[table->count++].value = value;
    return 0;
}

static inline s32 record_id_occurrence(Owner *owner, s32 id, s32 value, s32 repeat) {
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

s32 acquire_resource_slot(Owner *owner, s32 index, s32 shared) __asm__("func_8008716C");

s32 acquire_resource_slot(Owner *owner, s32 index, s32 shared) {
    SlotTable *slots = owner->table;
    ResourceRecord *record;

    if (index >= 3600) {
        return -1;
    }
    if (slots->slots[index].state == 0) {
        slots->slots[index].state = shared ? 2 : 1;
        record = &owner->records[index];
        if (ref_table_add_key(owner, record->key, record->value, 0) < 0) {
            return -1;
        }
        if (record_id_occurrence(owner, record->id, record->idValue, shared) < 0) {
            return -1;
        }
    } else if (shared != 0) {
        slots->slots[index].state++;
        record = &owner->records[index];
        if (record_id_occurrence(owner, record->id, record->idValue, shared) < 0) {
            return -1;
        }
    }
    return 0;
}
