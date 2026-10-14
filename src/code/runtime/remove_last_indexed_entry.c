#include "types.h"

typedef struct IndexedCollection {
    u8 pad00[8];
    u16 count;
} IndexedCollection;

extern void func_800DDE88(IndexedCollection *collection, u16 index);

void remove_last_indexed_entry(IndexedCollection *collection) __asm__("func_800DE098");

void remove_last_indexed_entry(IndexedCollection *collection)
{
    func_800DDE88(collection, (u16)(collection->count - 1));
}
