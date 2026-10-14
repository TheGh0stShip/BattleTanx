#include "types.h"

typedef struct RenderBucketItem {
    s32 value00;
    u32 value04;
    s32 value08;
    struct RenderBucketItem *next;
} RenderBucketItem;

typedef struct RenderBucket {
    u32 key;
    RenderBucketItem *lists[4];
    struct RenderBucket *next;
} RenderBucket;

typedef struct CachedMatrix {
    f32 mf[4][4];
    u32 address;
} CachedMatrix;

typedef struct RenderRecord {
    u8 pad00[0x14];
    s32 base;
} RenderRecord;

typedef struct RenderFrameRecord {
    u8 pad00[0x10];
    u32 cursor;
} RenderFrameRecord;

extern RenderRecord *get_current_render_record(void) __asm__("func_8007F00C");
extern RenderFrameRecord *get_render_frame_record(void) __asm__("func_8007F030");
extern void convert_float_matrix(CachedMatrix *src, u32 dst) __asm__("func_801146A0");
extern s32 gRenderItemCount __asm__("D_801B6C10");
extern s32 gRenderBucketCount __asm__("D_801B6C14");
extern RenderBucketItem gRenderItems[] __asm__("D_801B6C20");
typedef struct RenderBucketTable {
    RenderBucket buckets[300];
    RenderBucket *heads[0][32];
} RenderBucketTable;

extern RenderBucketTable gRenderBuckets __asm__("D_801BEC20");

s32 add_render_bucket_entry(u32 key, s32 arg1, CachedMatrix *src, u32 address, s32 arg4, s32 list, s32 layer) __asm__("func_80080728");

s32 add_render_bucket_entry(u32 key, s32 arg1, CachedMatrix *src, u32 address, s32 arg4, s32 list, s32 layer)
{
    RenderRecord *poolA = get_current_render_record();
    RenderFrameRecord *poolB = get_render_frame_record();
    s32 hash;
    RenderBucket *bucket;
    RenderBucketItem *item;

    if (src != 0) {
        if (src->address == 0) {
            if (poolB->cursor >= (u32)(poolA->base + 0xC000)) {
                return -1;
            }
            convert_float_matrix(src, poolB->cursor);
            src->address = poolB->cursor;
            poolB->cursor += 0x40;
        }
        address = src->address;
    }
    hash = ((key >> 2) * 17) & 0x1F;
    for (bucket = gRenderBuckets.heads[layer][hash]; bucket != 0; bucket = bucket->next) {
        if (bucket->key == key) {
            break;
        }
    }
    if (bucket == 0) {
        if (gRenderBucketCount == 300) {
            return -1;
        }
        bucket = &gRenderBuckets.buckets[gRenderBucketCount++];
        bucket->next = gRenderBuckets.heads[layer][hash];
        gRenderBuckets.heads[layer][hash] = bucket;
        bucket->key = key;
        bucket->lists[0] = 0;
        bucket->lists[1] = 0;
        bucket->lists[2] = 0;
        bucket->lists[3] = 0;
    }
    if (gRenderItemCount == 0x800) {
        return -1;
    }
    item = &gRenderItems[gRenderItemCount++];
    item->next = bucket->lists[list];
    bucket->lists[list] = item;
    item->value00 = arg1;
    item->value04 = address;
    item->value08 = arg4;
    return 0;
}
