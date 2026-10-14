#include "types.h"

extern f32 D_80074478;
extern f32 D_8007447C;

void transfer_step_when_below_limit(f32 *source, f32 *target) __asm__("func_800E10D0");

void transfer_step_when_below_limit(f32 *source, f32 *target)
{
    f32 value = *source;

    if (*target < value + D_80074478) {
        f32 step = D_8007447C;

        *source = value - step;
        *target += step;
    }
}
