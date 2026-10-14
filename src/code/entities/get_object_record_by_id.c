#include "types.h"

typedef struct ObjectRecordTable {
    u8 pad00[8];
    u16 count;
    u8 pad0A[2];
    s32 records;
} ObjectRecordTable;

extern ObjectRecordTable *gObjectRecordTable __asm__("D_80135834");

s32 get_object_record_by_id(u32 id) __asm__("func_800E0A48");

s32 get_object_record_by_id(u32 id)
{
    id &= 0xFFFF;
    if (id >= gObjectRecordTable->count) {
        return 0;
    }
    if (id == 0) {
        return 0;
    }
    return gObjectRecordTable->records + id * 8;
}
