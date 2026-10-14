#include "types.h"

typedef struct ALHeap {
    u8* base;
    u8* current;
    s32 length;
    s32 allocation_count;
} ALHeap;

void alHeapInit(ALHeap* heap, u8* base, s32 length) {
    s32 adjustment = (15 + 1) - ((s32)base & 15);

    if (adjustment != 16) {
        heap->base = base + adjustment;
    } else {
        heap->base = base;
    }
    heap->length = length;
    heap->current = heap->base;
    heap->allocation_count = 0;
}
