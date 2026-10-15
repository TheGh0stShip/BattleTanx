#include "types.h"

typedef struct U16RingBuffer {
    u16 *entries;
    u16 head;
    u16 pad06;
    u16 count;
    u16 pad0A;
    u16 capacity;
} U16RingBuffer;

u16 ring_buffer_peek_last(U16RingBuffer *buffer) __asm__("func_800DDD30");

u16 ring_buffer_peek_last(U16RingBuffer *buffer)
{
    u16 index;

    if (buffer->count == 0) {
        return 0;
    }
    index = buffer->count - 1;
    if (index < buffer->count) {
        return buffer->entries[(buffer->head + index) % buffer->capacity];
    }
    return 0;
}
