#include "types.h"

typedef struct StatusRing {
    u16 *entries;
    u16 head;
    u16 pad06;
    u16 count;
    u16 pad0A;
    u16 capacity;
    u8 allClear;
} StatusRing;

extern u8 get_mapped_runtime_status(u16 index) __asm__("func_800E19DC");

void update_ring_status_flag(StatusRing *ring) __asm__("func_800DDDA8");

void update_ring_status_flag(StatusRing *ring)
{
    s32 i;
    u16 position;
    u16 value;

    i = 0;
    ring->allClear = 1;
    if (ring->count != 0) {
        position = 0 & 0xFFFF;
        do {
            value = 0;
            if (position < ring->count) {
                value = ring->entries[(ring->head + position) % ring->capacity];
            }
            if (get_mapped_runtime_status((value / 3) & 0xFFFF)) {
                ring->allClear = 0;
            }
            i++;
            position = i & 0xFFFF;
        } while ((u32)(i & 0xFFFF) < ring->count);
    }
}
