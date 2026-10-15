#include "types.h"

typedef struct IndexedCollection {
    u8 pad00[8];
    u16 count;
} IndexedCollection;

extern s32 ring_buffer_advance(IndexedCollection *collection, u16 amount)
    __asm__("func_800DDE88");

void remove_last_indexed_entry(IndexedCollection *collection) __asm__("func_800DE098");

void remove_last_indexed_entry(IndexedCollection *collection)
{
    ring_buffer_advance(collection, (u16)(collection->count - 1));
}
