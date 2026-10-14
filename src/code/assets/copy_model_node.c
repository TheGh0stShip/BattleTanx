#include "types.h"

typedef struct NodeRecord {
    u8 count;
    u8 pad01;
    u16 first;
    u16 value04;
    u16 value06;
    u16 value08;
    u16 value0A;
} NodeRecord;

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
    u8 pad00[0xC];
    NodeRecord *nodes;
    u8 pad10[4];
    GroupRecord *groups;
    u8 pad18[0x10];
    CopyCounters *counters;
} SourceModel;

typedef struct DestModel {
    u8 pad00[0x570];
    NodeRecord *nodes;
    GroupRecord *groups;
} DestModel;

extern s16 copy_model_leaf(SourceModel *src, DestModel *dst, s32 index) __asm__("func_800880B4");

s32 copy_model_node(SourceModel *src, DestModel *dst, s32 index) __asm__("func_80088360");

static inline s32 copy_group(SourceModel *src, DestModel *dst, s32 index)
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

s32 copy_model_node(SourceModel *src, DestModel *dst, s32 index)
{
    s32 slot;
    NodeRecord *in;
    NodeRecord *out;
    s32 i;

    slot = src->counters->nodeCount++;
    out = &dst->nodes[slot];
    in = &src->nodes[index];
    out->value04 = in->value04;
    out->value06 = in->value06;
    out->value08 = in->value08;
    out->value0A = in->value0A;
    out->count = in->count;
    out->first = copy_group(src, dst, in->first);
    for (i = 1; i < out->count; i++) {
        copy_group(src, dst, in->first + i);
    }
    return slot;
}
