#include "types.h"

typedef struct GroupRecord {
    u8 count;
    u8 pad01;
    u16 first;
} GroupRecord;

typedef struct CopyCounters {
    u8 pad00[0x11400];
    s32 nodeCount;
    s32 groupCount;
} CopyCounters;

typedef struct SourceModel {
    u8 pad00[0x14];
    GroupRecord *groups;
    u8 pad18[0x10];
    CopyCounters *counters;
} SourceModel;

typedef struct DestModel {
    u8 pad00[0x574];
    GroupRecord *groups;
} DestModel;

extern s16 copy_model_leaf(SourceModel *src, DestModel *dst, s32 index) __asm__("func_800880B4");

s32 copy_model_group(SourceModel *src, DestModel *dst, s32 index) __asm__("func_80088280");

s32 copy_model_group(SourceModel *src, DestModel *dst, s32 index)
{
    s32 slot;
    GroupRecord *in;
    GroupRecord *out;
    s32 i;

    slot = src->counters->groupCount++;
    out = &dst->groups[slot];
    in = &src->groups[index];
    out->count = in->count;
    out->first = copy_model_leaf(src, dst, in->first);
    for (i = 1; i < out->count; i++) {
        copy_model_leaf(src, dst, in->first + i);
    }
    return slot;
}
