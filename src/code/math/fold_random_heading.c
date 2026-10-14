#include "types.h"

extern s32 random_heading_angle(void) __asm__("func_800F3BE4");

s32 fold_random_heading(void) __asm__("func_800F3BA8");

s32 fold_random_heading(void)
{
    s32 angle;
    register s32 folded __asm__("$4");

    angle = random_heading_angle() + 0x4000;
    folded = angle;
    if ((u32)(angle & 0xFFFF) > 0x8000U) {
        goto done;
    }
    folded = 0x8000 - angle;
done:
    return folded & 0xFFFF;
}
