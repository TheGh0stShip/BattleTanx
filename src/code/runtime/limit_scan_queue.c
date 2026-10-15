#include "types.h"

typedef struct ScanQueue {
    u16 *entries;
    u16 start;
    u8 pad06[2];
    u16 count;
    u8 pad0A[2];
    u16 capacity;
    u8 ready;
} ScanQueue;

extern u8 get_mapped_runtime_status(u16 index) __asm__("func_800E19DC");

void limit_scan_queue(ScanQueue *queue, u16 limit) __asm__("func_800DE0C0");

void limit_scan_queue(ScanQueue *queue, u16 limit)
{
    u16 i = 0;
    u16 value;

    if (limit < queue->count) {
        queue->count = limit;
        queue->ready = 1;
        for (; i < queue->count; i++) {
            value = 0;
            if (i < queue->count) {
                value = queue->entries[(queue->start + i) % queue->capacity];
            }
            if (get_mapped_runtime_status(value / 3)) {
                queue->ready = 0;
            }
        }
    }
}
