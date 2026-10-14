#include "types.h"

typedef struct Vec3f {
    f32 x;
    f32 y;
    f32 z;
} Vec3f;

/* Octagonal distance weights: major + minor * num / den. */
extern f32 D_8007444C;
extern f32 D_80074450;
extern f32 D_80074454;
extern f32 D_80074458;

#define FABS(v) ((v) > 0.0f ? (v) : -(v))

f32 approx_xz_distance(Vec3f *a, Vec3f *b) __asm__("func_800E0D54");

f32 approx_xz_distance(Vec3f *a, Vec3f *b) {
    f32 delta[2];
    f32 dx;
    f32 dz;

    delta[1] = FABS(a->x - b->x);
    delta[0] = FABS(a->z - b->z);
    dx = FABS(delta[1]);
    dz = FABS(delta[0]);
    return (dz < dx) ? dx + dz * D_8007444C / D_80074450 : dz + dx * D_80074454 / D_80074458;
}
