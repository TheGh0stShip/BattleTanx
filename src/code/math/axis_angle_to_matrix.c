#include "types.h"

extern f32 sin_radians(f32) __asm__("func_8011BE10");
extern f32 cos_radians(f32) __asm__("func_801113A0");
extern f32 D_800730BC; /* 1.0f */
extern f32 D_80126704; /* degrees to radians */

void axis_angle_to_matrix(f32 m[4][4], f32 x, f32 y, f32 z, f32 degrees) __asm__("func_800A7ABC");

void axis_angle_to_matrix(f32 m[4][4], f32 x, f32 y, f32 z, f32 degrees) {
    f32 angle = degrees * D_80126704;
    f32 s = sin_radians(angle);
    f32 c = cos_radians(angle);
    f32 one = D_800730BC;
    f32 tmp = one - c;
    f32 xy = x * y * tmp;
    f32 yz = y * z * tmp;
    f32 zx = z * x * tmp;

    tmp = x * x;
    m[0][0] = tmp + c * (one - tmp);
    m[2][1] = yz - x * s;
    m[1][2] = yz + x * s;
    tmp = y * y;
    m[1][1] = tmp + c * (one - tmp);
    m[2][0] = zx + y * s;
    m[0][2] = zx - y * s;
    tmp = z * z;
    m[2][2] = tmp + c * (one - tmp);
    m[1][0] = xy - z * s;
    m[0][1] = xy + z * s;
}
