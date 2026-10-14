#include "types.h"

extern f32 D_8007442C;
extern f32 D_80074430;
extern f32 D_80074434;
extern f32 D_80074438;

f32 ai_horizontal_length(f32 *offset) __asm__("func_800E0BC4");

f32 ai_horizontal_length(f32 *offset)
{
    f32 z;
    f32 x;

    z = offset[1];
    if (!(z > 0.0f)) {
        z = -z;
    }
    x = offset[0];
    if (!(x > 0.0f)) {
        x = -x;
    }
    if (x < z) {
        return z + x * D_80074434 / D_80074438;
    }
    return x + z * D_8007442C / D_80074430;
}
