#include "types.h"

typedef struct QuadPoint {
    f32 x;
    f32 y;
} QuadPoint;

extern f32 D_80071E94;
extern f32 D_80071E98;

void scale_quad_around_center(QuadPoint *points) __asm__("func_80092408");

void scale_quad_around_center(QuadPoint *points)
{
    f32 centerY;
    f32 centerX;
    f32 scale;
    f32 divisor;
    s32 i;

    divisor = D_80071E94;
    centerY = (((points[0].y + points[1].y) + points[2].y) + points[3].y) / divisor;
    centerX = (((points[0].x + points[1].x) + points[2].x) + points[3].x) / divisor;
    i = 0;
    scale = D_80071E98;
    for (; i < 4; i++) {
        points[i].y = centerY + ((points[i].y - centerY) * scale);
        points[i].x = centerX + ((points[i].x - centerX) * scale);
    }
}
