#include "types.h"

typedef struct PlanarPoint {
    f32 x;
    f32 y;
} PlanarPoint;

s32 planar_cross_is_negative(PlanarPoint *a, PlanarPoint *origin, PlanarPoint *c) __asm__("func_800E0EA8");

s32 planar_cross_is_negative(PlanarPoint *a, PlanarPoint *origin, PlanarPoint *c)
{
    f32 ay = a->y - origin->y;
    f32 ax = a->x - origin->x;
    f32 cx = c->x - origin->x;
    f32 cy = c->y - origin->y;

    return ay * cx - cy * ax < 0.0f;
}
