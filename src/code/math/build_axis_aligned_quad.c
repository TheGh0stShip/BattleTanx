#include "types.h"

typedef struct Vec3f {
    f32 x;
    f32 y;
    f32 z;
} Vec3f;

typedef struct QuadExtents {
    u8 pad00[0x28];
    f32 halfWidth;
    f32 halfHeight;
} QuadExtents;

extern f32 angle_cos(u16 angle) __asm__("func_800F3B40");
extern f32 angle_sin(u16 angle) __asm__("func_800F3AE0");

void build_axis_aligned_quad(QuadExtents *extents, Vec3f *center, Vec3f *corners) __asm__("func_800F46C8");

void build_axis_aligned_quad(QuadExtents *extents, Vec3f *center, Vec3f *corners) {
    f32 cosine = angle_cos(0);
    f32 offsetZ = extents->halfWidth * -angle_sin(0);
    f32 halfHeight = extents->halfHeight;
    f32 offsetX = extents->halfWidth * cosine;

    corners[0].z = corners[3].z = center->z + offsetZ;
    corners[0].x = corners[3].x = center->x + offsetX;
    corners[1].z = corners[2].z = center->z - offsetZ;
    corners[1].x = corners[2].x = center->x - offsetX;
    corners[0].y = corners[1].y = center->y - halfHeight;
    corners[2].y = corners[3].y = center->y + halfHeight;
}
