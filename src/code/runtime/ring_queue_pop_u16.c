#include "types.h"

typedef struct RingQueueU16 {
    u16 *data;
    u16 head;
    u16 value6;
    u16 count;
    u16 popCount;
    u16 capacity;
} RingQueueU16;

u16 ring_queue_pop_u16(RingQueueU16 *queue) __asm__("func_800DE280");

u16 ring_queue_pop_u16(RingQueueU16 *queue)
{
    u16 value;
    u16 head;
    u16 next;

    if (queue->count == 0) {
        return 0;
    }
    head = queue->head;
    next = (head + 1) % queue->capacity;
    value = queue->data[head];
    queue->popCount++;
    queue->count--;
    queue->head = next;
    return value;
}
