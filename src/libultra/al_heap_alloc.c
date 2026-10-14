#include "types.h"

typedef struct ALHeap {
    u8* base;
    u8* current;
    s32 length;
    s32 allocation_count;
} ALHeap;

void* alHeapDBAlloc(const char* file, s32 line, ALHeap* heap, s32 count, s32 size) {
    s32 byte_count = (count * size + 15) & ~15;
    u8* allocation = 0;

    if (heap->base + heap->length >= heap->current + byte_count) {
        allocation = heap->current;
        heap->current += byte_count;
    }
    return allocation;
}
