#include "types.h"

extern f32 angle_cos(u16 angle) __asm__("func_800F3B40");
extern f32 angle_sin(u16 angle) __asm__("func_800F3AE0");
extern f32 D_800730C8;

void apply_render_matrix_z_rotation(f32 src[4][4], f32 dst[4][4], u16 angle) __asm__("func_800A82B8");

static inline void set_identity(f32 matrix[4][4]) {
    s32 row;
    s32 column;

    for (row = 0; row < 4; row++) {
        for (column = 0; column < 4; column++) {
            if (row != column) {
                matrix[row][column] = 0.0f;
            } else {
                matrix[row][column] = D_800730C8;
            }
        }
    }
}

void apply_render_matrix_z_rotation(f32 src[4][4], f32 dst[4][4], u16 angle) {
    f32 rot[4][4];
    f32 c;
    f32 s;
    s32 i;
    s32 j;

    set_identity(rot);
    c = angle_cos(angle);
    s = angle_sin(angle);
    rot[0][1] = s;
    rot[0][0] = c;
    rot[1][1] = c;
    rot[1][0] = -s;
    for (j = 0; j < 3; j++) {
        for (i = 0; i < 3; i++) {
            dst[i][j] = src[i][0] * rot[0][j] + src[i][1] * rot[1][j] + src[i][2] * rot[2][j];
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
