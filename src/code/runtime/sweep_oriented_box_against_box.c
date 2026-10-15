#include "types.h"

typedef struct OrientedBox {
    s16 value00;
    s16 x;
    s16 z;
    s16 minX;
    s16 minZ;
    s16 maxX;
    s16 maxZ;
    s16 value0E;
    u16 angle;
    u16 value12;
} OrientedBox;

typedef struct BoxPolygon {
    f32 points[8];
} BoxPolygon;

extern f32 angle_sin(u16 angle) __asm__("func_800F3AE0");
extern f32 angle_cos(u16 angle) __asm__("func_800F3B40");
extern void func_8010B740(OrientedBox *box, BoxPolygon *polygon);
extern s32 func_8010AC90(f64 *bounds, BoxPolygon *polygon, f32 *velocity, s32 arg3, f32 *hit);

s32 sweep_oriented_box_against_box(OrientedBox *moving, f32 *velocity, OrientedBox *fixed, s32 arg3, f32 *hit) __asm__("func_8010B9C8");

s32 sweep_oriented_box_against_box(OrientedBox *moving, f32 *velocity, OrientedBox *fixed, s32 arg3, f32 *hit) {
    OrientedBox local;
    f64 bounds[4];
    f32 localVelocity[2];
    f32 localHit[2];
    BoxPolygon polygon;
    f32 dx;
    f32 dz;
    f32 cosine;
    f32 sine;
    f32 c;
    f32 s;

    bounds[0] = fixed->minX;
    bounds[1] = fixed->minZ;
    bounds[3] = fixed->maxX;
    bounds[2] = fixed->maxZ;
    dx = moving->x - fixed->x;
    dz = moving->z - fixed->z;
    cosine = angle_cos(fixed->angle);
    sine = angle_sin(fixed->angle);
    local.x = cosine * dx - sine * dz;
    local.z = sine * dx + cosine * dz;
    local.angle = moving->angle - fixed->angle;
    local.minX = moving->minX;
    local.minZ = moving->minZ;
    local.maxX = moving->maxX;
    local.maxZ = moving->maxZ;
    s = angle_sin(fixed->angle);
    c = angle_cos(fixed->angle);
    localVelocity[1] = c * velocity[1] + -s * velocity[0];
    localVelocity[0] = s * velocity[1] + c * velocity[0];
    func_8010B740(&local, &polygon);
    if (func_8010AC90(bounds, &polygon, localVelocity, arg3, localHit)) {
        velocity[1] = c * localVelocity[1] + s * localVelocity[0];
        velocity[0] = -s * localVelocity[1] + c * localVelocity[0];
        hit[1] = c * localHit[1] + s * localHit[0];
        hit[0] = -s * localHit[1] + c * localHit[0];
        return 1;
    }
    return 0;
}
