#include "types.h"

typedef struct RotatedQuad {
    u8 pad00[0x18];
    u16 angle;
    u8 pad1A[0xE];
    f32 halfWidth;
    f32 halfHeight;
} RotatedQuad;

extern f32 angle_sin(u16 angle) __asm__("func_800F3AE0");
extern f32 angle_cos(u16 angle) __asm__("func_800F3B40");

void build_rotated_quad_corners(RotatedQuad *quad, f32 *center, f32 corners[4][3]) __asm__("func_8010CD4C");

void build_rotated_quad_corners(RotatedQuad *quad, f32 *center, f32 corners[4][3]) {
    u16 angle = quad->angle;
    f32 cosValue = angle_cos(angle);
    f32 dz = quad->halfWidth * -angle_sin(angle);
    f32 h = quad->halfHeight;
    f32 dx = quad->halfWidth * cosValue;

    corners[0][2] = corners[3][2] = center[2] + dz;
    corners[0][0] = corners[3][0] = center[0] + dx;
    corners[1][2] = corners[2][2] = center[2] - dz;
    corners[1][0] = corners[2][0] = center[0] - dx;
    corners[0][1] = corners[1][1] = center[1] - h;
    corners[2][1] = corners[3][1] = center[1] + h;
}
