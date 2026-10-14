#include "types.h"

typedef struct ObjectWordTable {
    u8 pad00[0xA];
    u16 linkCount;
    u8 pad0C[0x4];
    s32 words;
} ObjectWordTable;

extern ObjectWordTable *gObjectRecordTable __asm__("D_80135834");

s32 get_object_link_word(u32 index) __asm__("func_800E09F4");

s32 get_object_link_word(u32 index)
{
    u32 link;

    index &= 0xFFFF;
    link = (u16)(index / 3);
    if (link >= gObjectRecordTable->linkCount) {
        return 0;
    }
    if (link == 0) {
        return 0;
    }
    return gObjectRecordTable->words + index * 4;
}
