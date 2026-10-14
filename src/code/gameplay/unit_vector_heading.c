#include "types.h"

typedef struct HeadingVectorUnit {
    u8 pad00[0x38C];
    f32 value38C;
    f32 value390;
} HeadingVectorUnit;

extern float sqrtf(float);
extern s32 radians_to_angle(f32 radians) __asm__("func_800F3BE4");

u16 unit_vector_heading(HeadingVectorUnit *unit) __asm__("func_8009FC0C");

u16 unit_vector_heading(HeadingVectorUnit *unit) {
    f32 x = unit->value38C;
    f32 z = unit->value390;
    f32 length;
    f32 cosine;
    u16 angle;

    if (x == 0.0f && z == 0.0f) {
        return 0;
    }
    length = sqrtf(x * x + z * z);
    cosine = z / length;
    if (x < 0.0f) {
        angle = -radians_to_angle(cosine);
    } else {
        angle = radians_to_angle(cosine);
    }
    return angle;
}
