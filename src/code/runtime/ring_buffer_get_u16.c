#include "types.h"

typedef struct U16RingBuffer {
    u16 *data;
    u16 start;
    u16 head;
    u16 count;
    u16 value0A;
    u16 capacity;
} U16RingBuffer;

u16 ring_buffer_get_u16(U16RingBuffer *ring, u16 index) __asm__("func_800DDCCC");

u16 ring_buffer_get_u16(U16RingBuffer *ring, u16 index) {
    if (index < ring->count) {
        return ring->data[(ring->start + index) % ring->capacity];
    }
    return 0;
}
