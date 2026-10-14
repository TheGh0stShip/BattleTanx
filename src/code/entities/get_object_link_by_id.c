#include "types.h"

typedef struct ObjectLinkTable {
    u8 pad00[0xA];
    u16 linkCount;
    u8 pad0C[0x8];
    s32 links;
} ObjectLinkTable;

#define OBJECT_LINK_SIZE 0xC

extern ObjectLinkTable *gObjectRecordTable __asm__("D_80135834");

s32 get_object_link_by_id(u32 id) __asm__("func_800E09B0");

s32 get_object_link_by_id(u32 id)
{
    id &= 0xFFFF;
    if (id >= gObjectRecordTable->linkCount) {
        return 0;
    }
    if (id == 0) {
        return 0;
    }
    return gObjectRecordTable->links + id * OBJECT_LINK_SIZE;
}
