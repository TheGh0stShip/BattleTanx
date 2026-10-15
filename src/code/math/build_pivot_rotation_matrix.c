#include "types.h"

extern f32 angle_sin(u32 angle) __asm__("func_800F3AE0");
extern f32 angle_cos(u16 angle) __asm__("func_800F3B40");

void build_pivot_rotation_matrix(f32 m[4][4], f32 *pivot, f32 *position, u16 angleZ, u16 angleY, u16 angleX)
    __asm__("func_800A86E4");

void build_pivot_rotation_matrix(f32 m[4][4], f32 *pivot, f32 *position, u16 angleZ, u16 angleY, u16 angleX) {
    f32 sinX, cosX, sinY, cosY, sinZ, cosZ;
    f32 t[3];

    m[0][3] = 0.0f;
    m[1][3] = 0.0f;
    m[2][3] = 0.0f;
    m[3][0] = position[0];
    m[3][1] = position[1];
    m[3][2] = position[2];
    sinX = angle_sin(angleX);
    cosX = angle_cos(angleX);
    sinY = angle_sin(angleY);
    cosY = angle_cos(angleY);
    sinZ = angle_sin(angleZ);
    cosZ = angle_cos(angleZ);
    m[0][0] = cosY * cosZ;
    m[0][1] = cosY * sinZ;
    m[0][2] = -sinY;
    m[1][0] = sinX * sinY * cosZ - cosX * sinZ;
    m[1][1] = sinX * sinY * sinZ + cosX * cosZ;
    m[1][2] = sinX * cosY;
    m[2][0] = cosX * sinY * cosZ + sinX * sinZ;
    m[2][1] = cosX * sinY * sinZ - sinX * cosZ;
    m[2][2] = cosX * cosY;
    t[0] = pivot[0] * m[0][0] + pivot[1] * m[1][0] + pivot[2] * m[2][0] + m[3][0];
    t[1] = pivot[0] * m[0][1] + pivot[1] * m[1][1] + pivot[2] * m[2][1] + m[3][1];
    t[2] = pivot[0] * m[0][2] + pivot[1] * m[1][2] + pivot[2] * m[2][2] + m[3][2];
    m[3][0] = t[0];
    m[3][1] = t[1];
    m[3][2] = t[2];
}
