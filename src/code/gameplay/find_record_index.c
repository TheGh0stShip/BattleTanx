#include "types.h"

typedef struct ListRecord {
    s32 key;
    u8 pad04[0xC];
} ListRecord;

typedef struct ListOwner {
    u8 pad00[0xA374];
    s32 count;
    ListRecord records[1];
} ListOwner;

typedef struct ListHandle {
    u8 pad00[0x28];
    ListOwner *owner;
} ListHandle;

s32 find_record_index(ListHandle *handle, s32 key) __asm__("func_8008805C");

s32 find_record_index(ListHandle *handle, s32 key) {
    ListOwner *owner = handle->owner;
    s32 i;

    for (i = 0; i < owner->count; i++) {
        if (owner->records[i].key == key) {
            return i;
        }
    }
    return 0;
}
