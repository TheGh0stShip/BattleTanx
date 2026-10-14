#include "types.h"

typedef struct PlanePoint {
    f32 x;
    f32 z;
} PlanePoint;

s32 points_equal_2d(PlanePoint *a, PlanePoint *b) __asm__("func_800E1098");

s32 points_equal_2d(PlanePoint *a, PlanePoint *b)
{
    s32 equal;

    equal = 0;
    if (a->z == b->z && a->x == b->x) {
        equal = 1;
    }
    return equal;
}
