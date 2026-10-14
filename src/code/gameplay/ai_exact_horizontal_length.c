#include "types.h"

extern float sqrtf(float);

f32 ai_exact_horizontal_length(f32 *offset) __asm__("func_800E0C44");

f32 ai_exact_horizontal_length(f32 *offset) {
    return sqrtf(offset[1] * offset[1] + offset[0] * offset[0]);
}
