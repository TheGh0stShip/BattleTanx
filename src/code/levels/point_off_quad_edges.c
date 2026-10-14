#include "types.h"

typedef struct QuadPoint {
    f32 x;
    f32 z;
} QuadPoint;

/* Returns nonzero unless the point lies exactly on the line through a and b. */
static inline s32 point_off_edge(QuadPoint *a, QuadPoint *b, QuadPoint *point)
{
    f32 terms[4];
    s32 off;

    terms[3] = point->z - a->z;
    terms[2] = point->x - a->x;
    terms[1] = b->x - a->x;
    terms[0] = a->z - b->z;
    off = 0;
    if (terms[3] * terms[1] + terms[2] * terms[0] != 0.0f) {
        off = 1;
    }
    return off;
}

s32 point_off_quad_edges(QuadPoint *quad, QuadPoint *point) __asm__("func_80094774");

s32 point_off_quad_edges(QuadPoint *quad, QuadPoint *point)
{
    if (point_off_edge(&quad[0], &quad[1], point) && point_off_edge(&quad[1], &quad[2], point)
        && point_off_edge(&quad[2], &quad[3], point) && point_off_edge(&quad[3], &quad[0], point)) {
        return 1;
    }
    return 0;
}
