#include "types.h"

extern float sqrtf(float);
extern f32 D_80074F3C;
extern f32 D_80074F40;

f32 vec3_normalize(f32 *v) __asm__("func_800F3A24");
f32 vec3_normalize(f32 *v) {
    f32 length = sqrtf(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
    f32 scale;

    if (length != 0.0f) {
        scale = D_80074F3C / length;
    } else {
        scale = D_80074F40;
    }
    v[0] *= scale;
    v[1] *= scale;
    v[2] *= scale;
    return length;
}
