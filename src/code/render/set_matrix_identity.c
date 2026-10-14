#include "types.h"

extern f32 D_800730B0;

void set_matrix_identity(f32 matrix[4][4]) __asm__("func_800A7650");

void set_matrix_identity(f32 matrix[4][4])
{
    s32 row;
    s32 column;

    for (row = 0; row < 4; row++) {
        for (column = 0; column < 4; column++) {
            if (row != column) {
                matrix[row][column] = 0.0f;
            } else {
                matrix[row][column] = D_800730B0;
            }
        }
    }
}
