#include "types.h"

typedef struct Point2f {
    f32 x;
    f32 y;
} Point2f;

static inline s32 intersect_segments_2d(Point2f a, Point2f b, Point2f c, Point2f d, Point2f *out) {
    f64 bay = b.y - a.y;
    f64 bax = b.x - a.x;
    f64 dcy = d.y - c.y;
    f64 acy = a.y - c.y;
    f64 dcx = d.x - c.x;
    f64 acx = a.x - c.x;
    f64 denominator = dcy * bax - dcx * bay;
    f64 ua;
    f64 ub;
    s32 result;

    if (denominator == 0.0) {
        if (acy * bax - acx * bay != 0.0) {
            return 0;
        }
        return 2;
    }
    ua = (acy * bax - acx * bay) / denominator;
    ub = (acy * dcx - acx * dcy) / denominator;
    if (((ua >= 0.0) & (ua <= 1.0)) && ((ub >= 0.0) & (ub <= 1.0))) {
        result = 1;
    } else {
        result = 0;
    }
    out->y = c.y + ua * (d.y - c.y);
    out->x = c.x + ua * (d.x - c.x);
    return result;
}

s32 clip_segment_to_edge(Point2f a, Point2f b, Point2f c, Point2f d, Point2f *delta, Point2f *hit) __asm__("func_8010AA6C");

s32 clip_segment_to_edge(Point2f a, Point2f b, Point2f c, Point2f d, Point2f *delta, Point2f *hit) {
    Point2f point;

    if (intersect_segments_2d(a, b, c, d, &point) == 1) {
        delta->y = d.y - point.y;
        delta->x = d.x - point.x;
        hit->y = point.y;
        hit->x = point.x;
        return 1;
    }
    return 0;
}
