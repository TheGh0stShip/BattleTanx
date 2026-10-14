#include "types.h"

typedef struct LeafSource {
    s32 id;
    u16 value04;
    u8 pad06[0x2];
    s32 romOffset;
    s32 size;
} LeafSource;

typedef struct LeafRecord {
    s32 value00;
    s32 dataOffset;
    s16 value08;
    u8 pad0A[0x2];
} LeafRecord;

typedef struct LeafLookup {
    s32 id;
    u8 pad04[0x4];
    s32 offset;
    u8 pad0C[0x4];
} LeafLookup;

typedef struct CopyCounters {
    u8 pad00[0x936C];
    s32 lookupCount;
    LeafLookup lookups[0x809];
    u8 pad11400[0x8];
    s32 leafCount;
    s32 dataSize;
} CopyCounters;

typedef struct SourceModel {
    u8 pad00[0x18];
    LeafSource *leaves;
    u8 pad1C[0xC];
    CopyCounters *counters;
} SourceModel;

typedef struct DestModel {
    u8 pad00[0x578];
    LeafRecord *leaves;
    u8 pad57C[0x4];
    u64 *data;
} DestModel;

extern void rom_dma_read(u8 *romAddress, u8 *destination, s32 size) __asm__("func_80077930");
extern u8 gBundle3DFD10End[] __asm__("D_B03EA970");
extern void func_80085290(u64 *data, s32 count, u64 *out);
extern void func_80086DC0(u64 *data, s32 arg1);
extern s32 D_80125C30;

s32 copy_model_leaf(SourceModel *src, DestModel *dst, s32 index) __asm__("func_800880B4");

s32 copy_model_leaf(SourceModel *src, DestModel *dst, s32 index) {
    CopyCounters *counters = src->counters;
    s32 slot;
    LeafSource *in;
    LeafRecord *out;
    s32 i;
    s32 found;
    s32 id;
    CopyCounters *lookups;

    slot = counters->leafCount++;
    out = &dst->leaves[slot];
    in = &src->leaves[index];
    if (in->value04 != 0) {
        out->value08 = ((in->value04 & 0x7FF) >> 3) | (in->value04 & 0xF800);
    } else {
        out->value08 = 0;
    }
    lookups = src->counters;
    id = in->id;
    for (i = 0; i < lookups->lookupCount; i++) {
        if (lookups->lookups[i].id == id) {
            found = i;
            goto done;
        }
    }
    found = 0;
done:
    out->value00 = counters->lookups[found].offset / 8;
    out->dataOffset = counters->dataSize / 8;
    counters->dataSize += (in->size + 7) & ~7;
    rom_dma_read(gBundle3DFD10End + in->romOffset, (u8 *)&dst->data[out->dataOffset], in->size);
    func_80085290(&dst->data[out->dataOffset], in->size / 8, &dst->data[out->dataOffset]);
    func_80086DC0(&dst->data[out->dataOffset], D_80125C30);
    return slot;
}
