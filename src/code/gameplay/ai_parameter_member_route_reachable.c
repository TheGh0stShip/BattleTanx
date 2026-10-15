#include "types.h"

typedef struct RouteBuffer {
    u8 data[0x200];
} RouteBuffer;

typedef struct PlanarPoint {
    f32 z;
    f32 x;
} PlanarPoint;

typedef struct RouteFlags {
    u8 pad00[5];
    u8 enabled;
} RouteFlags;

typedef struct RouteMember {
    u8 pad00[0x24];
    f32 x;
    u8 pad28[4];
    f32 z;
    u8 pad30[0x6C];
    u32 mode;
    u8 padA0[4];
    PlanarPoint goal;
    u8 padAC[4];
    RouteFlags *flags;
} RouteMember;

typedef struct AiParameterContext {
    u8 pad00[8];
    RouteMember *member;
} AiParameterContext;

extern f32 D_80074864;
extern f32 D_80074868;
extern f32 ai_horizontal_distance(PlanarPoint *a, PlanarPoint *b) __asm__("func_800E0C8C");
extern f32 get_scaled_difficulty(void) __asm__("func_800DDC68");
extern void initialize_route_buffer(RouteBuffer *buffer) __asm__("func_800DDCA4");
extern u16 find_route(RouteBuffer *buffer, PlanarPoint *from, PlanarPoint *to, s32 arg3, s32 arg4)
    __asm__("func_800DE664");

f32 ai_parameter_member_route_reachable(AiParameterContext *context) __asm__("func_800E9318");

f32 ai_parameter_member_route_reachable(AiParameterContext *context)
{
    RouteMember *member = context->member;
    PlanarPoint point;
    RouteBuffer buffer;
    PlanarPoint farPoint;
    RouteBuffer farBuffer;
    f32 distance;
    PlanarPoint *goal;
    PlanarPoint *farGoal;
    f32 result;
    u16 found;

    switch (member->mode) {
    case 6:
        point.x = member->x;
        point.z = context->member->z;
        goal = &member->goal;
        distance = ai_horizontal_distance(&point, goal);
        if (get_scaled_difficulty() < distance) {
            break;
        }
        initialize_route_buffer(&buffer);
        found = find_route(&buffer, goal, &point, 1, 0);
        result = D_80074864;
        if (found != 0) {
            return result;
        }
        break;
    case 7:
        farPoint.x = member->x;
        farPoint.z = context->member->z;
        farGoal = &member->goal;
        initialize_route_buffer(&farBuffer);
        found = find_route(&farBuffer, farGoal, &farPoint, 1, 0);
        result = D_80074864;
        if (found != 0) {
            return result;
        }
        break;
    case 5:
        return member->flags->enabled ? D_80074868 : 0.0f;
    }
    return 0.0f;
}
