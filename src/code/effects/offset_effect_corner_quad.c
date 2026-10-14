#include "types.h"

typedef struct {
    f32 x;
    f32 y;
} Point2f;

typedef struct {
    Point2f points[4];
} Quad2f;

extern Quad2f D_80071E64;

void offset_effect_corner_quad(Point2f *origin, Point2f *out) __asm__("func_80091108");
void offset_effect_corner_quad(Point2f *origin, Point2f *out) {
    Quad2f quad;
    s32 i;

    quad = D_80071E64;
    for (i = 0; i < 4; i++) {
        out[i].y = quad.points[i].y + origin->y;
        out[i].x = quad.points[i].x + origin->x;
    }
}
