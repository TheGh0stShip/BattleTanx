#include "types.h"

extern f32 ai_horizontal_length(f32 *offset) __asm__("func_800E0BC4");
extern u16 radians_to_angle(f32 radians) __asm__("func_800F3BE4");

u16 heading_between_points(f32 *from, f32 *to) __asm__("func_800E2820");

u16 heading_between_points(f32 *from, f32 *to)
{
    f32 offset[2];
    f32 length;
    u16 heading;

    offset[1] = to[1] - from[1];
    offset[0] = to[0] - from[0];
    length = ai_horizontal_length(offset);
    offset[1] /= length;
    offset[0] /= length;
    if (offset[1] < 0.0f) {
        heading = -radians_to_angle(offset[0]);
    } else {
        heading = radians_to_angle(offset[0]);
    }
    return heading;
}
