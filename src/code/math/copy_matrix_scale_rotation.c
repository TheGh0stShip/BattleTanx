#include "types.h"

void copy_matrix_scale_rotation(f32 src[4][4], f32 dst[4][4], f32 scale) __asm__("func_800A7ECC");

void copy_matrix_scale_rotation(f32 src[4][4], f32 dst[4][4], f32 scale) {
    s32 i;
    s32 j;

    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            if (i < 3 && j < 3) {
                dst[i][j] = src[i][j] * scale;
            } else {
                dst[i][j] = src[i][j];
            }
        }
    }
}
