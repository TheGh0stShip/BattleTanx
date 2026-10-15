#include "types.h"

extern f32 D_800730C4;

void build_camera_view_matrix(f32 src[4][4], f32 view[4][4], f32 eye[3], f32 at[3]) __asm__("func_800A8034");

static inline void set_identity(f32 matrix[4][4]) {
    s32 row;
    s32 column;

    for (row = 0; row < 4; row++) {
        for (column = 0; column < 4; column++) {
            if (row != column) {
                matrix[row][column] = 0.0f;
            } else {
                matrix[row][column] = D_800730C4;
            }
        }
    }
}

void build_camera_view_matrix(f32 src[4][4], f32 view[4][4], f32 eye[3], f32 at[3]) {
    f32 dot[3];
    s32 i;
    s32 j;

    eye[0] = src[3][0];
    eye[1] = src[3][1];
    eye[2] = src[3][2];
    at[0] = eye[0] + src[2][0];
    at[1] = eye[1] + src[2][1];
    at[2] = eye[2] + src[2][2];
    set_identity(view);
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            if (i == 1) {
                view[j][1] = src[i][j];
            } else {
                view[j][i] = -src[i][j];
            }
        }
    }
    dot[0] = eye[0] * view[0][0] + eye[1] * view[1][0] + eye[2] * view[2][0];
    dot[1] = eye[0] * view[0][1] + eye[1] * view[1][1] + eye[2] * view[2][1];
    dot[2] = eye[0] * view[0][2] + eye[1] * view[1][2] + eye[2] * view[2][2];
    view[3][0] = -dot[0];
    view[3][1] = -dot[1];
    view[3][2] = -dot[2];
}
