#include "types.h"

typedef struct {
    s32 key;
    s32 value;
    s32 pad08;
    s32 refCount;
} RefEntry;

typedef struct {
    u8 pad0000[0x936C];
    s32 count;
    RefEntry entries[256];
} RefTable;

typedef struct {
    u8 pad00[0x28];
    RefTable *table;
} RefOwner;

s32 ref_table_add_key(RefOwner *owner, s32 key, s32 value, s32 addRef) __asm__("func_80086F3C");

s32 ref_table_add_key(RefOwner *owner, s32 key, s32 value, s32 addRef) {
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
