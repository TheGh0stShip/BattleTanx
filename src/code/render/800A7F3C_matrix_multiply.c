#include "types.h"

typedef struct {
    f32 m[4][4];
} Matrix4f;

void func_800A7F3C(Matrix4f* first, Matrix4f* second, Matrix4f* output) {
    s32 column;
    s32 row;

    for (column = 0; column < 4; column++) {
        for (row = 0; row < 4; row++) {
            output->m[row][column] =
                first->m[row][0] * second->m[0][column] +
                first->m[row][1] * second->m[1][column] +
                first->m[row][2] * second->m[2][column] +
                first->m[row][3] * second->m[3][column];
        }
    }
}

void func_800A7FC0(Matrix4f* first, Matrix4f* second, Matrix4f* output) {
    s32 column;
    s32 row;

    for (column = 0; column < 3; column++) {
        for (row = 0; row < 3; row++) {
            output->m[row][column] =
                first->m[row][0] * second->m[0][column] +
                first->m[row][1] * second->m[1][column] +
                first->m[row][2] * second->m[2][column];
        }
    }
}
