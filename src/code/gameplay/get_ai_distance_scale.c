#include "types.h"

extern f32 gAiDistanceScale __asm__("D_800744E4");

f32 get_ai_distance_scale(void) __asm__("func_800E1ED0");

f32 get_ai_distance_scale(void)
{
    return gAiDistanceScale;
}
