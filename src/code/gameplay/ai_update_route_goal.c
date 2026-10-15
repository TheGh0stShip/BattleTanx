#include "types.h"

typedef struct U16RingBuffer {
    u16 *data;
    u16 start;
    u16 head;
    u16 count;
    u16 value0A;
    u16 capacity;
} U16RingBuffer;

typedef struct RouteGoal {
    f32 x;
    f32 z;
    f32 distance;
    f32 timer;
    u16 waypoint;
    u16 node;
    u8 active;
    u8 pending;
    u8 valid;
} RouteGoal;

typedef struct AiUnit {
    u8 pad000[0x9C];
    s32 state;
    u8 pad0A0[0x134 - 0xA0];
    U16RingBuffer route;
    u8 pad144[0x334 - 0x144];
    RouteGoal goal;
} AiUnit;

typedef struct AiRouteState {
    s32 mode;
    RouteGoal *goal;
    u8 pad08[9];
    u8 pending;
} AiRouteState;

extern s32 func_800DDE88(U16RingBuffer *, u16);
extern u16 ring_buffer_get_u16(U16RingBuffer *, u16) __asm__("func_800DDCCC");
extern void get_waypoint_midpoint(u16, RouteGoal *) __asm__("func_800E0B00");
extern f32 ai_horizontal_distance(f32 *, f32 *) __asm__("func_800E0C8C");
extern f32 D_800744E0;

f32 ai_update_route_goal(AiUnit *unit, AiRouteState *state, f32 *position)
    __asm__("func_800E1D40");

f32 ai_update_route_goal(AiUnit *unit, AiRouteState *state, f32 *position)
{
    register f32 result __asm__("$f20") = 0.0f;
    register AiRouteState *routeState __asm__("$19") = state;
    register f32 *reference __asm__("$20") = position;
    register U16RingBuffer *route __asm__("$16") = &unit->route;
    register RouteGoal *goal __asm__("$17") = &unit->goal;
    s32 pending;
    s32 active;
    s32 expired;
    f32 distance;
    u32 waypoint;
    u16 index;

    if (unit->state == 0) {
        goto done;
    }
    pending = 0;
    if (routeState->mode == 8) {
        pending = routeState->pending != 0;
    }
    active = 0;
    if (goal->waypoint != 0 || goal->active != 0) {
        active = 1;
    }
    expired = goal->timer < 0.0f;
    if (active && !pending) {
        if (!expired) {
            if (goal->valid == 0) {
                routeState->goal = goal;
                goto done;
            }
            distance = goal->distance;
            if (D_800744E0 < distance) {
                routeState->goal = goal;
                goto done;
            }
        } else {
            goal->pending = 1;
            routeState->goal = goal;
            goto done;
        }
    }
    if (pending) {
        routeState->pending = 0;
    }
    routeState->goal = 0;
    goal->active = 0;
    goal->pending = 0;
    goal->waypoint = 0;
    if (active && func_800DDE88(route, 1) == 0) {
        goto done;
    }
    waypoint = ring_buffer_get_u16(route, 0);
    index = waypoint;
    if (index == 0) {
        goto done;
    }
    get_waypoint_midpoint(index, goal);
    routeState->goal = goal;
    goal->distance = ai_horizontal_distance(reference, &goal->x);
    goal->waypoint = waypoint;
    goal->node = index / 3;
done:
    return result;
}
