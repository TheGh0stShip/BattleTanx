#include "types.h"

typedef struct HeadingVector {
    u8 pad00[0x14];
    f32 x;
    f32 z;
} HeadingVector;

typedef struct HeadingObject {
    u8 pad00[0x74];
    f32 facingX;
    u8 pad78[0x4];
    f32 facingZ;
} HeadingObject;

extern s32 cosine_to_angle(f32 cosine) __asm__("func_800F3BE4");
extern u16 angle_distance(u16 a, u16 b) __asm__("func_800F3D0C");
extern f32 sqrtf(f32 value);

u32 choose_heading_facing_vector(HeadingObject *object, HeadingVector *vector)
    __asm__("func_8009FD94");

u32 choose_heading_facing_vector(HeadingObject *object, HeadingVector *vector)
{
    f32 x;
    f32 z;
    u16 heading16;
    s32 heading;
    s32 target;

    x = vector->x;
    z = vector->z;
    if ((x == 0.0f) & (z == 0.0f)) {
        target = 0;
    } else {
        f32 length = sqrtf(x * x + z * z);
        f32 ratio = z / length;
        if (x < 0.0f) {
            target = -cosine_to_angle(ratio);
        } else {
            target = cosine_to_angle(ratio);
        }
        target &= 0xFFFF;
    }
    if (object->facingX < 0.0f) {
        heading = -cosine_to_angle(object->facingZ);
    } else {
        heading = cosine_to_angle(object->facingZ);
    }
    heading16 = heading;
    if (angle_distance(target, heading16) > 0x4000) {
        return (heading + 0x8000) & 0xFFFF;
    }
    return heading16;
}
