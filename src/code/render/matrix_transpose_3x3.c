#include "types.h"

typedef struct Matrix4f {
    f32 m[4][4];
} Matrix4f;

void matrix_transpose_3x3(Matrix4f *source, Matrix4f *destination)
    __asm__("func_800A81F0");

void matrix_transpose_3x3(Matrix4f *source, Matrix4f *destination)
{
    s32 column;
    s32 row;

    for (column = 0; column < 3; column++) {
        for (row = 0; row < 3; row++) {
            destination->m[row][column] = source->m[column][row];
        }
    }
}
