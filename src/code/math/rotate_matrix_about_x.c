#include "types.h"

extern f32 angle_cos(u16 angle) __asm__("func_800F3B40");
extern f32 angle_sin(u16 angle) __asm__("func_800F3AE0");
extern f32 D_800730D0;

void rotate_matrix_about_x(f32 src[4][4], f32 dst[4][4], u16 angle) __asm__("func_800A8580");

void rotate_matrix_about_x(f32 src[4][4], f32 dst[4][4], u16 angle) {
    f32 rot[4][4];
    s32 i;
    s32 j;
    s32 row;
    s32 col;
    f32 c;
    f32 s;

    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            if (i != j) {
                rot[i][j] = 0.0f;
            } else {
                rot[i][i] = D_800730D0;
            }
        }
    }
    c = angle_cos(angle);
    s = angle_sin(angle);
    rot[1][2] = s;
    rot[1][1] = c;
    rot[2][2] = c;
    rot[2][1] = -s;
    for (col = 0; col < 3; col++) {
        for (row = 0; row < 3; row++) {
            dst[row][col] = src[row][0] * rot[0][col] + src[row][1] * rot[1][col] + src[row][2] * rot[2][col];
        }
    }
    dst[0][3] = src[0][3];
    dst[1][3] = src[1][3];
    dst[2][3] = src[2][3];
    dst[3][3] = src[3][3];
    dst[3][2] = src[3][2];
    dst[3][1] = src[3][1];
    dst[3][0] = src[3][0];
}
