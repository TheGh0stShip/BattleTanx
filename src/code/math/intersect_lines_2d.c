#include "types.h"

typedef struct Point2f {
    f32 x;
    f32 y;
} Point2f;

extern f32 D_8007445C;
extern f32 D_80074460;
extern f32 D_80074464;
extern f32 D_80074468;
extern f32 D_8007446C;
extern f32 D_80074470;
extern f32 D_80074474;

s32 intersect_lines_2d(Point2f *a0, Point2f *a1, Point2f *b0, Point2f *b1,
                       Point2f *out) __asm__("func_800E0EFC");

s32 intersect_lines_2d(Point2f *a0, Point2f *a1, Point2f *b0, Point2f *b1,
                       Point2f *out)
{
    f32 dy;
    f32 slopeA;
    f32 slopeB;
    f32 interceptA;
    f32 interceptB;
    f32 denominator;
    f32 y;

    dy = a1->y - a0->y;
    if ((dy > 0.0f) ? (dy < D_8007445C) : (-dy < D_80074460)) {
        slopeA = D_80074464;
    } else {
        slopeA = (a1->x - a0->x) / dy;
    }
    dy = b1->y - b0->y;
    if ((dy > 0.0f) ? (dy < D_80074468) : (-dy < D_8007446C)) {
        slopeB = D_80074470;
    } else {
        slopeB = (b1->x - b0->x) / dy;
    }
    interceptA = a0->x - a0->y * slopeA;
    interceptB = b0->x - b0->y * slopeB;
    if (slopeA == slopeB) {
        if (interceptA == interceptB) {
            out->y = (a0->y + a1->y) / D_80074474;
            out->x = (a0->x + a1->x) / D_80074474;
            return 1;
        }
        return 0;
    }
    denominator = slopeA - slopeB;
    y = 0.0f;
    if (denominator != 0.0f) {
        y = (slopeA * y - interceptA) / denominator;
    }
    out->y = y;
    out->x = slopeA * y + interceptA;
    return 1;
}
