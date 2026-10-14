#include "types.h"

typedef struct U16RingBuffer {
    u16 *data;
    u16 start;
    u16 head;
    u16 count;
    u16 value0A;
    u16 capacity;
} U16RingBuffer;

s32 ring_buffer_push_u16(U16RingBuffer *ring, u16 value) __asm__("func_800DE1B4");

s32 ring_buffer_push_u16(U16RingBuffer *ring, u16 value) {
    u16 slot;

    if (ring->count < ring->capacity) {
        if (ring->count + ring->value0A == ring->capacity) {
            slot = ring->head;
            ring->head = (slot + 1) % ring->capacity;
            ring->value0A--;
        } else {
            slot = (ring->start + ring->count) % ring->capacity;
        }
        ring->data[slot] = value;
        ring->count++;
        return 1;
    }
    return 0;
}
