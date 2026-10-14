#include "types.h"

extern f32 ai_normalized_elapsed_time(s32 startTime) __asm__("func_800E95A8");

f32 ai_parameter_elapsed_time(void) __asm__("func_800E775C");

f32 ai_parameter_elapsed_time(void)
{
    return ai_normalized_elapsed_time(0);
}
