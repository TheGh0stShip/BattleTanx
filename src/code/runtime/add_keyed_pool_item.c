#include "types.h"

typedef struct PoolVec3 {
    f32 x;
    f32 y;
    f32 z;
} PoolVec3;

typedef struct PoolItem {
    s32 value00;
    PoolVec3 position;
    f32 value10;
    f32 value14;
    u16 value18;
    u8 pad1A[2];
    struct PoolItem *next;
} PoolItem;

typedef struct PoolKey {
    u32 key;
    PoolItem *lists[4];
    struct PoolKey *next;
} PoolKey;

typedef struct PoolKeyTable {
    PoolKey keys[32];
    PoolKey *buckets[1][32];
} PoolKeyTable;

extern void clear_memory(void *address, s32 size) __asm__("func_80110C00");
extern s32 gRuntimePoolHead2 __asm__("D_801B6C18");
extern s32 gRuntimePoolHead3 __asm__("D_801B6C1C");
extern PoolItem gPoolItems[256] __asm__("D_801C0BC0");
extern PoolKeyTable gPoolKeys __asm__("D_801C2BC0");

s32 add_keyed_pool_item(u32 key, s32 value, PoolVec3 *position, f32 a, f32 b, u16 c, s32 list, s32 table)
    __asm__("func_80080910");

/* Finds or allocates the hashed key record, then pushes a new item onto one of its four lists. */
s32 add_keyed_pool_item(u32 key, s32 value, PoolVec3 *position, f32 a, f32 b, u16 c, s32 list, s32 table)
{
    s32 hash = ((key >> 2) * 17) & 0x1F;
    PoolKey *entry;
    PoolItem *item;

    for (entry = gPoolKeys.buckets[table][hash]; entry != 0; entry = entry->next) {
        if (entry->key == key) {
            break;
        }
    }
    if (entry == 0) {
        if (gRuntimePoolHead3 == 32) {
            return -1;
        }
        entry = &gPoolKeys.keys[gRuntimePoolHead3++];
        entry->next = gPoolKeys.buckets[table][hash];
        gPoolKeys.buckets[table][hash] = entry;
        entry->key = key;
        clear_memory(entry->lists, sizeof(entry->lists));
    }
    if (gRuntimePoolHead2 == 256) {
        return -1;
    }
    item = &gPoolItems[gRuntimePoolHead2++];
    item->next = entry->lists[list];
    entry->lists[list] = item;
    item->position = *position;
    item->value10 = a;
    item->value14 = b;
    item->value18 = c;
    item->value00 = value;
    return 0;
}
