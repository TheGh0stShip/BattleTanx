#include "types.h"

typedef struct OrientedBox {
    s16 value00;
    s16 x;
    s16 z;
    s16 minX;
    s16 maxX;
    s16 minZ;
    s16 maxZ;
    s16 value0E;
    u16 angle;
} OrientedBox;

typedef struct BoxCorner {
    f32 z;
    f32 x;
} BoxCorner;

typedef struct CornerBounds {
    f32 minX;
    f32 maxX;
    f32 minZ;
    f32 maxZ;
} CornerBounds;

extern f32 angle_sin(u16 angle) __asm__("func_800F3AE0");
extern f32 angle_cos(u16 angle) __asm__("func_800F3B40");
extern void compute_rotated_quad(OrientedBox *box, BoxCorner *corners) __asm__("func_8010A474");

s32 oriented_boxes_separated(OrientedBox *local, OrientedBox *reference, OrientedBox *other)
    __asm__("func_8010A680");

/* Moves `other` into the frame of `reference` (stored in `local`) and tests the
 * resulting corner bounds against the reference extents. */
s32 oriented_boxes_separated(OrientedBox *local, OrientedBox *reference, OrientedBox *other)
{
    BoxCorner corners[4];
    CornerBounds bounds;
    f32 dx;
    f32 dz;
    f32 cosine;
    f32 sine;
    s32 i;

    dx = other->x - reference->x;
    dz = other->z - reference->z;
    cosine = angle_cos(reference->angle);
    sine = angle_sin(reference->angle);
    local->x = cosine * dx - sine * dz;
    local->z = sine * dx + cosine * dz;
    local->angle = other->angle - reference->angle;
    local->minX = other->minX;
    local->maxX = other->maxX;
    local->minZ = other->minZ;
    local->maxZ = other->maxZ;
    compute_rotated_quad(local, corners);
    bounds.minX = corners[0].x;
    bounds.maxX = corners[0].x;
    bounds.minZ = corners[0].z;
    bounds.maxZ = corners[0].z;
    for (i = 1; i < 4; i++) {
        if (corners[i].x < bounds.minX) {
            bounds.minX = corners[i].x;
        }
        if (corners[i].x > bounds.maxX) {
            bounds.maxX = corners[i].x;
        }
        if (corners[i].z < bounds.minZ) {
            bounds.minZ = corners[i].z;
        }
        if (corners[i].z > bounds.maxZ) {
            bounds.maxZ = corners[i].z;
        }
    }
    if (reference->maxX < bounds.minX) {
        return 1;
    }
    if (bounds.maxX < reference->minX) {
        return 1;
    }
    if (reference->maxZ < bounds.minZ) {
        return 1;
    }
    if (bounds.maxZ < reference->minZ) {
        return 1;
    }
    return 0;
}
