#include "types.h"

typedef struct RouteQueue {
    u16 *data;
    u16 head;
    u16 tail;
    u16 count;
    u16 free;
    u16 capacity;
    u8 valid;
} RouteQueue;

extern u8 get_mapped_runtime_status(u16 cell) __asm__("func_800E19DC");
extern void func_800DE664(RouteQueue *queue, void *from, s32 to,
                         s32 allowPartial, s32 includeStart);
extern u16 D_80135838;
extern u8 D_80328450[];

static inline u16 route_queue_get(RouteQueue *queue, u16 index)
{
    if (index >= queue->count) {
        return 0;
    }
    return queue->data[(queue->head + index) % queue->capacity];
}

static inline void route_queue_revalidate(RouteQueue *queue)
{
    s32 i = 0;

    if (queue->count != 0) {
        queue->count = 0;
        queue->valid = 1;
        for (; (u16)i < queue->count; i++) {
            if (get_mapped_runtime_status(route_queue_get(queue, i) / 3)) {
                queue->valid = 0;
            }
        }
    }
}

static inline u8 route_queue_push(RouteQueue *queue, u32 value)
{
    u16 slot;

    if (queue->count >= queue->capacity) {
        return 0;
    }
    if (queue->count + queue->free == queue->capacity) {
        slot = queue->tail;
        queue->tail = (slot + 1) % queue->capacity;
        queue->free--;
    } else {
        slot = (queue->head + queue->count) % queue->capacity;
    }
    queue->data[slot] = value;
    queue->count++;
    return 1;
}

static inline u16 route_queue_last(RouteQueue *queue)
{
    if (queue->count == 0) {
        return 0;
    }
    return route_queue_get(queue, queue->count - 1);
}

u16 rebuild_route_from_current_cell(RouteQueue *queue, s32 target)
    __asm__("func_800DE3EC");

u16 rebuild_route_from_current_cell(RouteQueue *queue, s32 target)
{
    volatile s32 frameSlot;

    route_queue_revalidate(queue);
    route_queue_push(queue, D_80135838 * 3);
    func_800DE664(queue, D_80328450, target, 0, 1);
    return route_queue_last(queue) / 3;
}
