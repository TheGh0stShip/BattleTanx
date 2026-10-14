#include "types.h"

typedef struct PlanePoint {
    f32 x;
    f32 z;
} PlanePoint;

/* 2.0f in this object's .rodata. */
extern f32 D_800744B4;

void midpoint_2d(PlanePoint *a, PlanePoint *b, PlanePoint *out) __asm__("func_800E16DC");

void midpoint_2d(PlanePoint *a, PlanePoint *b, PlanePoint *out)
{
    out->z = (a->z + b->z) / D_800744B4;
    out->x = (a->x + b->x) / D_800744B4;
}
