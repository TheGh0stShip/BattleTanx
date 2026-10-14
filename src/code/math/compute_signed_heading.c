#include "types.h"

typedef struct HeadingSource {
    u8 pad00[0xB0];
    f32 heading;
    u8 padB4[0x4];
    f32 direction;
} HeadingSource;

extern u16 radians_to_angle(f32 radians) __asm__("func_800F3BE4");

u16 compute_signed_heading(HeadingSource *source) __asm__("func_800A4254");

u16 compute_signed_heading(HeadingSource *source)
{
    u16 heading;

    if (source->direction < 0.0f) {
        heading = -radians_to_angle(source->heading);
    } else {
        heading = radians_to_angle(source->heading);
    }
    return heading;
}
