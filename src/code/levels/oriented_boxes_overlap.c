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

typedef struct OverlapNormal {
    f32 x;
    f32 z;
} OverlapNormal;

extern f32 angle_sin(u16 angle) __asm__("func_800F3AE0");
extern f32 angle_cos(u16 angle) __asm__("func_800F3B40");
extern s32 oriented_boxes_separated(OrientedBox *local, OrientedBox *reference, OrientedBox *other)
    __asm__("func_8010A680");

s32 oriented_boxes_overlap(OrientedBox *a, OrientedBox *b, OverlapNormal *normal) __asm__("func_8010A8A8");

s32 oriented_boxes_overlap(OrientedBox *a, OrientedBox *b, OverlapNormal *normal) {
    OrientedBox localA;
    OrientedBox localB;
    f32 dx;
    f32 dz;
    f32 cosine;
    f32 sine;
    f32 negSine;
    f32 normalSine;
    f32 normalCosine;

    if (oriented_boxes_separated(&localA, a, b)) {
        return 0;
    }
    if (oriented_boxes_separated(&localB, b, a)) {
        return 0;
    }
    dx = a->x - b->x;
    dz = a->z - b->z;
    cosine = angle_cos(b->angle);
    sine = angle_sin(b->angle);
    localA.x = cosine * dx - sine * dz;
    localA.z = sine * dx + cosine * dz;
    localA.angle = a->angle - b->angle;
    localA.minX = a->minX;
    localA.maxX = a->maxX;
    localA.minZ = a->minZ;
    localA.maxZ = a->maxZ;
    normalSine = angle_sin(b->angle);
    negSine = -normalSine;
    normalCosine = angle_cos(b->angle);
    normal->z = 0.0f;
    normal->x = 0.0f;
    if (localA.x < 0) {
        normal->x = normalSine;
        normal->z = -normalCosine;
    } else if (localA.x > 0) {
        normal->z = normalCosine;
        normal->x = negSine;
    }
    if (localA.z < 0) {
        normal->z = normal->z + negSine;
        normal->x = normal->x - normalCosine;
    } else if (localA.z > 0) {
        normal->z = normal->z - negSine;
        normal->x = normal->x + normalCosine;
    }
    return 1;
}
