#include "types.h"

typedef struct Vec2 {
    f32 x;
    f32 y;
} Vec2;

extern s32 intersect_segments_2d(Vec2 a, Vec2 b, Vec2 c, Vec2 d, Vec2 *hit) __asm__("func_8010BC10");

s32 sweep_box_polygon_against_bounds(f64 *bounds, Vec2 *poly, Vec2 *vel, Vec2 *hit, f32 *normal) __asm__("func_8010AC90");

s32 sweep_box_polygon_against_bounds(f64 *bounds, Vec2 *poly, Vec2 *vel, Vec2 *hit, f32 *normal)
{
    Vec2 from;
    Vec2 to;
    Vec2 cross;

    if (poly[2].y < bounds[0]) {
        f64 t;

        if (vel->y <= 0.0) {
            return 0;
        }
        if (poly[2].y + vel->y < bounds[0]) {
            return 0;
        }
        t = (bounds[0] - poly[2].y) * vel->x;
        if ((bounds[2] - poly[2].x) * vel->y < t || t < (bounds[3] - poly[2].x) * vel->y) {
            from.y = bounds[0] - vel->y;
            from.x = bounds[2] - vel->x;
            to.y = bounds[0];
            to.x = bounds[2];
            if (intersect_segments_2d(poly[3], poly[2], from, to, &cross) == 1) {
                vel->y = to.y - cross.y;
                vel->x = to.x - cross.x;
                hit->y = cross.y;
                hit->x = cross.x;
                normal[1] = -0.707f;
                normal[0] = 0.707f;
                return 1;
            }
            from.x = bounds[3] - vel->x;
            to.x = bounds[3];
            if (intersect_segments_2d(poly[2], poly[1], from, to, &cross) == 1) {
                vel->y = to.y - cross.y;
                vel->x = to.x - cross.x;
                hit->y = cross.y;
                hit->x = cross.x;
                normal[1] = -0.707f;
                normal[0] = -0.707f;
                return 1;
            }
            return 0;
        }
        vel->x = t / vel->y;
        vel->y = bounds[0] - poly[2].y;
        hit->y = bounds[0];
        hit->x = poly[2].x + vel->x;
        normal[1] = -1.0f;
        normal[0] = 0.0f;
        return 2;
    }
    if (bounds[1] < poly[0].y) {
        f64 t;

        if (vel->y >= 0.0) {
            return 0;
        }
        if (bounds[1] < poly[0].y + vel->y) {
            return 0;
        }
        t = (bounds[1] - poly[0].y) * vel->x;
        if (t < (bounds[2] - poly[0].x) * vel->y || (bounds[3] - poly[0].x) * vel->y < t) {
            from.y = bounds[1] - vel->y;
            from.x = bounds[2] - vel->x;
            to.y = bounds[1];
            to.x = bounds[2];
            if (intersect_segments_2d(poly[0], poly[3], from, to, &cross) == 1) {
                vel->y = to.y - cross.y;
                vel->x = to.x - cross.x;
                hit->y = cross.y;
                hit->x = cross.x;
                normal[1] = 0.707f;
                normal[0] = 0.707f;
                return 1;
            }
            from.x = bounds[3] - vel->x;
            to.x = bounds[3];
            if (intersect_segments_2d(poly[1], poly[0], from, to, &cross) == 1) {
                vel->y = to.y - cross.y;
                vel->x = to.x - cross.x;
                hit->y = cross.y;
                hit->x = cross.x;
                normal[1] = 0.707f;
                normal[0] = -0.707f;
                return 1;
            }
            return 0;
        }
        vel->x = t / vel->y;
        vel->y = bounds[1] - poly[0].y;
        hit->y = bounds[1];
        hit->x = poly[0].x + vel->x;
        normal[1] = 1.0f;
        normal[0] = 0.0f;
        return 2;
    }
    if (bounds[2] < poly[3].x) {
        f64 t;

        if (vel->x >= 0.0) {
            return 0;
        }
        if (bounds[2] < poly[3].x + vel->x) {
            return 0;
        }
        t = (bounds[2] - poly[3].x) * vel->y;
        if ((bounds[0] - poly[3].y) * vel->x < t || t < (bounds[1] - poly[3].y) * vel->x) {
            from.y = bounds[0] - vel->y;
            from.x = bounds[2] - vel->x;
            to.y = bounds[0];
            to.x = bounds[2];
            if (intersect_segments_2d(poly[3], poly[2], from, to, &cross) == 1) {
                vel->y = to.y - cross.y;
                vel->x = to.x - cross.x;
                hit->y = cross.y;
                hit->x = cross.x;
                normal[1] = -0.707f;
                normal[0] = 0.707f;
                return 1;
            }
            from.y = bounds[1] - vel->y;
            to.y = bounds[1];
            if (intersect_segments_2d(poly[0], poly[3], from, to, &cross) == 1) {
                vel->y = to.y - cross.y;
                vel->x = to.x - cross.x;
                hit->y = cross.y;
                hit->x = cross.x;
                normal[1] = 0.707f;
                normal[0] = 0.707f;
                return 1;
            }
            return 0;
        }
        vel->y = t / vel->x;
        vel->x = bounds[2] - poly[3].x;
        hit->y = poly[3].y + vel->y;
        hit->x = bounds[2];
        normal[1] = 0.0f;
        normal[0] = 1.0f;
        return 2;
    }
    if (poly[1].x < bounds[3]) {
        f64 t;

        if (vel->x <= 0.0) {
            return 0;
        }
        if (poly[1].x + vel->x < bounds[3]) {
            return 0;
        }
        t = (bounds[3] - poly[1].x) * vel->y;
        if (t < (bounds[0] - poly[1].y) * vel->x || (bounds[1] - poly[1].y) * vel->x < t) {
            from.y = bounds[0] - vel->y;
            from.x = bounds[3] - vel->x;
            to.y = bounds[0];
            to.x = bounds[3];
            if (intersect_segments_2d(poly[2], poly[1], from, to, &cross) == 1) {
                vel->y = to.y - cross.y;
                vel->x = to.x - cross.x;
                hit->y = cross.y;
                hit->x = cross.x;
                normal[1] = -0.707f;
                normal[0] = -0.707f;
                return 1;
            }
            from.y = bounds[1] - vel->y;
            to.y = bounds[1];
            if (intersect_segments_2d(poly[1], poly[0], from, to, &cross) == 1) {
                vel->y = to.y - cross.y;
                vel->x = to.x - cross.x;
                hit->y = cross.y;
                hit->x = cross.x;
                normal[1] = 0.707f;
                normal[0] = -0.707f;
                return 1;
            }
            return 0;
        }
        vel->y = t / vel->x;
        vel->x = bounds[3] - poly[1].x;
        hit->y = poly[1].y + vel->y;
        hit->x = bounds[3];
        normal[1] = 0.0f;
        normal[0] = -1.0f;
        return 2;
    }
    to.y = bounds[0];
    to.x = bounds[3];
    from.y = to.y - vel->y;
    from.x = to.x - vel->x;
    if (intersect_segments_2d(poly[2], poly[1], from, to, &cross) == 1) {
        vel->y = to.y - cross.y;
        vel->x = to.x - cross.x;
        hit->y = cross.y;
        hit->x = cross.x;
        normal[1] = -0.707f;
        normal[0] = -0.707f;
        return 1;
    }
    to.x = bounds[2];
    from.x = to.x - vel->x;
    if (intersect_segments_2d(poly[3], poly[2], from, to, &cross) == 1) {
        vel->y = to.y - cross.y;
        vel->x = to.x - cross.x;
        hit->y = cross.y;
        hit->x = cross.x;
        normal[1] = -0.707f;
        normal[0] = 0.707f;
        return 1;
    }
    to.y = bounds[1];
    from.y = to.y - vel->y;
    if (intersect_segments_2d(poly[0], poly[3], from, to, &cross) == 1) {
        vel->y = to.y - cross.y;
        vel->x = to.x - cross.x;
        hit->y = cross.y;
        hit->x = cross.x;
        normal[1] = 0.707f;
        normal[0] = 0.707f;
        return 1;
    }
    to.x = bounds[3];
    from.x = to.x - vel->x;
    if (intersect_segments_2d(poly[1], poly[0], from, to, &cross) == 1) {
        vel->y = to.y - cross.y;
        vel->x = to.x - cross.x;
        hit->y = cross.y;
        hit->x = cross.x;
        normal[1] = 0.707f;
        normal[0] = -0.707f;
        return 1;
    }
    return 0;
}
