#include "types.h"

typedef struct Point2f {
    f32 x;
    f32 z;
} Point2f;

s32 point_off_edge(Point2f *a, Point2f *b, Point2f *point) __asm__("func_80094704");

s32 point_off_edge(Point2f *a, Point2f *b, Point2f *point)
{
    f32 terms[4];
    s32 off;

    terms[3] = point->z - a->z;
    terms[2] = point->x - a->x;
    terms[1] = b->x - a->x;
    terms[0] = a->z - b->z;
    off = 1;
    if (terms[3] * terms[1] + terms[2] * terms[0] == 0.0f) {
        off = 0;
    }
    return off;
}
