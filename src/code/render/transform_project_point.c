#include "types.h"

typedef struct ProjectedPoint {
    f32 x;
    f32 y;
    f32 z;
} ProjectedPoint;

extern f32 D_800730C0;

void transform_project_point(f32 matrix[4][4], ProjectedPoint *input,
                             ProjectedPoint *output) __asm__("func_800A7DBC");

void transform_project_point(f32 matrix[4][4], ProjectedPoint *input,
                             ProjectedPoint *output)
{
    f32 scale;

    output->x = (((input->x * matrix[0][0]) + (input->y * matrix[1][0])) +
                 (input->z * matrix[2][0])) + matrix[3][0];
    output->y = (((input->x * matrix[0][1]) + (input->y * matrix[1][1])) +
                 (input->z * matrix[2][1])) + matrix[3][1];
    output->z = (((input->x * matrix[0][2]) + (input->y * matrix[1][2])) +
                 (input->z * matrix[2][2])) + matrix[3][2];
    scale = D_800730C0 /
            ((((input->x * matrix[0][3]) + (input->y * matrix[1][3])) +
              (input->z * matrix[2][3])) + matrix[3][3]);
    {
        f32 x = output->x * scale;
        f32 y = output->y * scale;
        f32 z;

        output->x = x;
        output->y = y;
        z = output->z;
        output->z = z * scale;
    }
}
