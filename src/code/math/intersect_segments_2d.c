#include "types.h"

typedef struct Vec2 {
    f32 x;
    f32 y;
} Vec2;

s32 intersect_segments_2d(Vec2 a, Vec2 b, Vec2 c, Vec2 d, Vec2 *hit) __asm__("func_8010BC10");

s32 intersect_segments_2d(Vec2 a, Vec2 b, Vec2 c, Vec2 d, Vec2 *hit)
{
    f64 abX;
    f64 abY;
    f64 cdX;
    f64 cdY;
    f64 acY;
    f64 acX;
    f64 denom;
    f64 t;
    f64 s;
    s32 result;

    abY = b.y - a.y;
    abX = b.x - a.x;
    cdY = d.y - c.y;
    cdX = d.x - c.x;
    acY = a.y - c.y;
    acX = a.x - c.x;
    denom = cdY * abX - cdX * abY;

    if (denom == 0.0) {
        if (acY * abX - acX * abY != 0.0) {
            return 0;
        }
        return 2;
    }
    t = (acY * abX - acX * abY) / denom;
    s = (acY * cdX - acX * cdY) / denom;
    if (((t >= 0.0) & (t <= 1.0)) && ((s >= 0.0) & (s <= 1.0))) {
        result = 1;
    } else {
        result = 0;
    }
    hit->y = c.y + t * (d.y - c.y);
    hit->x = c.x + t * (d.x - c.x);
    return result;
}
