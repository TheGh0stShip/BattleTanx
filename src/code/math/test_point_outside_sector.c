#include "types.h"
typedef struct {
    f32 value00;
    f32 value04;
    f32 value08;
    f32 value0C;
    f32 value10;
    f32 value14;
    u8 value18;
} SectorShape;
extern f64 D_80072020;
extern f64 D_80072028;

s32 test_point_outside_sector(f32 x, f32 y, f32 r, SectorShape *c) __asm__("func_800941E0");

/* Returns 0 when the offset point lies inside the shape's rotated sector (widened by r), 1 otherwise. */
s32 test_point_outside_sector(f32 x, f32 y, f32 r, SectorShape *c) {
    f32 dx;
    f32 dy;
    f32 a;
    f32 b;

    if (c->value18 != 0) {
        return 0;
    }
    dy = y + c->value14;
    dx = x + c->value10;
    a = c->value00 * dy + c->value04 * dx;
    b = c->value08 * dx - c->value0C * dy;
    if (a <= 0.0f) {
        return 1;
    }
    if (b > 0.0f) {
        if (b - r * D_80072020 < a) {
            return 0;
        }
    } else {
        if (-b - r * D_80072028 < a) {
            return 0;
        }
    }
    return 1;
}
