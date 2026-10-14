#include "types.h"

extern f32 sin_radians(f32) __asm__("func_8011BE10");
extern f32 cos_radians(f32) __asm__("func_801113A0");
extern f32 D_80126700; /* degrees to radians */

void euler_angles_to_matrix(f32 m[4][4], f32 *angles) __asm__("func_800A7964");

void euler_angles_to_matrix(f32 m[4][4], f32 *angles) {
    f32 rz = angles[2] * D_80126700;
    f32 ry = angles[1] * D_80126700;
    f32 rx = angles[0] * D_80126700;
    f32 sz = sin_radians(rz);
    f32 cz = cos_radians(rz);
    f32 sy = sin_radians(ry);
    f32 cy = cos_radians(ry);
    f32 sx = sin_radians(rx);
    f32 cx = cos_radians(rx);

    m[0][0] = cy * cx;
    m[0][1] = cy * sx;
    m[0][2] = -sy;
    m[1][0] = sz * sy * cx - cz * sx;
    m[1][1] = sz * sy * sx + cz * cx;
    m[1][2] = sz * cy;
    m[2][0] = cz * sy * cx + sz * sx;
    m[2][1] = cz * sy * sx - sz * cx;
    m[2][2] = cz * cy;
}
