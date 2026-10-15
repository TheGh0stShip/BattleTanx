#include "types.h"

typedef struct PathNode {
    u8 active;
    u8 open;
    u16 parent;
    u8 pad04[0x14];
} PathNode;

typedef struct RouteQueue {
    u16 *data;
    u16 head;
    u16 tail;
    u16 count;
    u16 free;
    u16 capacity;
    u8 valid;
} RouteQueue;

typedef struct ObjectLink {
    u16 value00;
    u16 neighbor;
} ObjectLink;

typedef struct PathGraph {
    PathNode nodes[1];
    u8 pad18[0x11948 - 0x18];
    RouteQueue *queue;
    u8 pad1194C[0x11956 - 0x1194C];
    u16 goalNode;
} PathGraph;

extern u8 get_mapped_runtime_status(u16 cell) __asm__("func_800E19DC");
extern ObjectLink *get_object_link_by_id(u32 id) __asm__("func_800E09B0");

void build_route_from_path(PathGraph *graph) __asm__("func_800DF7D0");

static inline RouteQueue *get_route_queue(PathGraph *graph)
{
    return graph->queue;
}

static inline u16 get_goal_node(PathGraph *graph)
{
    return graph->goalNode;
}

static inline s32 route_queue_push(RouteQueue *queue, u16 value)
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

void build_route_from_path(PathGraph *graph)
{
    volatile s32 frameSlot;
    RouteQueue *queue;
    u16 node;
    u16 parent;
    u16 i = 0;
    u16 value;
    ObjectLink *links;

    queue = get_route_queue(graph);
    node = get_goal_node(graph);
    route_queue_revalidate(queue);
    parent = graph->nodes[node].parent;
    while (parent != 0) {
        links = get_object_link_by_id(node);
        value = 0;
        for (i = 0; i < 3; i++) {
            if (parent == links[i].neighbor / 3) {
                value = node * 3 + i;
                break;
            }
        }
        if (!route_queue_push(queue, value)) {
            break;
        }
        node = parent;
        parent = graph->nodes[node].parent;
    }
}
