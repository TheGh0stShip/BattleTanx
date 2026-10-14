#include "types.h"

typedef struct PackedRangeOwner {
    u8 pad00[0x8];
    u16 packedRange;
} PackedRangeOwner;

extern u32 D_801B4AA0;

s32 select_packed_range_index(PackedRangeOwner *owner, s32 index) __asm__("func_80082458");

s32 select_packed_range_index(PackedRangeOwner *owner, s32 index) {
    if (index >= 0) {
        return (owner->packedRange & 0x7FF) + index;
    }
    if (index == -1) {
        return (owner->packedRange & 0x7FF) + D_801B4AA0 % (owner->packedRange >> 11);
    }
    return (owner->packedRange & 0x7FF) + (D_801B4AA0 >> 1) % (owner->packedRange >> 11);
}
