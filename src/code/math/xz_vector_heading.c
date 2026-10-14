#include "types.h"

typedef struct HeadingVector {
    u8 pad00[0x14];
    f32 x;
    f32 z;
} HeadingVector;

extern float sqrtf(float);
extern s32 radians_to_angle(f32 radians) __asm__("func_800F3BE4");

u16 xz_vector_heading(HeadingVector *vec) __asm__("func_8009FCD0");

u16 xz_vector_heading(HeadingVector *vec) {
    f32 x = vec->x;
    f32 z = vec->z;
    f32 length;
    f32 cosine;
    u16 angle;

    if ((x == 0.0f) & (z == 0.0f)) {
        return 0;
    }
    length = sqrtf(x * x + z * z);
    cosine = z / length;
    if (x < 0.0f) {
        angle = -radians_to_angle(cosine);
    } else {
        angle = radians_to_angle(cosine);
    }
    return angle;
}
