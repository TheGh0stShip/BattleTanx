#include "types.h"

typedef struct MotionAccumulator { u8 pad00[0x90]; s32 floor; s32 count; f32 x; f32 y; f32 z; } MotionAccumulator;
void reset_motion_accumulator(MotionAccumulator *state) __asm__("func_80078814");
void reset_motion_accumulator(MotionAccumulator *state)
{
    register f32 zero = 0.0f;
    state->floor = -1000;
    state->count = 0;
    state->z = zero;
    state->y = zero;
    state->x = zero;
}
