#include "types.h"

typedef struct RouteQueue {
    u16 *entries;
    u16 head;
    u16 tail;
    u16 count;
    u16 free;
    u16 capacity;
    u8 valid;
} RouteQueue;

extern u8 get_mapped_runtime_status(u16 index) __asm__("func_800E19DC");
extern u16 rebuild_route_from_current_cell(RouteQueue *queue, s32 target)
    __asm__("func_800DE3EC");
extern s32 choose_cell_exit_edges(u16 node, s32 target, s32 requireNearOpen,
                                  s32 requireFarOpen, u16 *nearEdge,
                                  u16 *farEdge) __asm__("func_800E004C");

static inline void revalidate_route_queue(RouteQueue *queue)
{
    s32 i;
    u16 position;
    u16 value;

    i = 0;
    position = 0;
    queue->valid = 1;
    if (position < queue->count) {
        do {
            value = 0;
            if (position < queue->count) {
                value = queue->entries[(queue->head + position) % queue->capacity];
            }
            if (get_mapped_runtime_status((value / 3) & 0xFFFF)) {
                queue->valid = 0;
            }
            i++;
            position = i & 0xFFFF;
        } while ((u32)(i & 0xFFFF) < queue->count);
    }
}

static inline void push_route_entry(RouteQueue *queue, u16 value)
{
    u16 slot;

    if (queue->count < queue->capacity) {
        if (queue->count + queue->free == queue->capacity) {
            slot = queue->tail;
            queue->tail = (slot + 1) % queue->capacity;
            queue->free--;
        } else {
            slot = (queue->head + queue->count) % queue->capacity;
        }
        queue->entries[slot] = value;
        queue->count++;
    }
}

u16 extend_route_three_steps(RouteQueue *queue, s32 routeTarget, s32 target)
    __asm__("func_800E031C");

u16 extend_route_three_steps(RouteQueue *queue, s32 routeTarget, s32 target)
{
    u16 node;
    u16 nearEdge;
    u16 farEdge;
    u32 steps;
    s32 i;

    node = rebuild_route_from_current_cell(queue, routeTarget);
    steps = 3;
    if (queue->count != 0) {
        queue->count = 0;
        revalidate_route_queue(queue);
    }
    for (i = 0; (i & 0xFFFF) < steps; i++) {
        if (!choose_cell_exit_edges(node & 0xFFFF, target, 0, 1,
                                    &nearEdge, &farEdge)) {
            return 0;
        }
        push_route_entry(queue, farEdge);
        node = farEdge / 3;
    }
    return node;
}
