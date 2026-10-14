#include "types.h"

typedef struct Point2 {
    f32 x;
    f32 y;
} Point2;

typedef struct PointTable {
    u8 pad00[0xC];
    Point2 *points;
} PointTable;

typedef struct TriangleIndex {
    u16 point;
    u8 pad02[2];
} TriangleIndex;

extern PointTable *D_80135834;
extern f32 D_800744B0;

void compute_waypoint_triangle_centroid(TriangleIndex *corners, Point2 *out) __asm__("func_800E1648");

void compute_waypoint_triangle_centroid(TriangleIndex *corners, Point2 *out) {
    Point2 sum;
    u16 i;

    sum.y = 0.0f;
    sum.x = 0.0f;
    for (i = 0; i < 3; i++) {
        TriangleIndex *corner = &corners[i];
        Point2 *p = &D_80135834->points[corner->point];
        sum.y += p->y;
        sum.x += p->x;
    }
    sum.y /= D_800744B0;
    sum.x /= D_800744B0;
    out->y = sum.y;
    out->x = sum.x;
}
