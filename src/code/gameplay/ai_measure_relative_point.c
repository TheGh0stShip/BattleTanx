#include "types.h"

typedef struct MeasureEntity {
    u8 pad000[0x24];
    f32 x;
    u8 pad028[4];
    f32 z;
    u8 pad030[0x3FC - 0x30];
    f32 value3FC;
    f32 value400;
} MeasureEntity;

extern f32 vec2_length(f32 *v) __asm__("func_800E0C44");
extern s32 radians_to_angle(f32 radians) __asm__("func_800F3BE4");

static inline s32 wrap_angle_delta(s32 delta) {
    if (delta > 0) {
        if (delta > 0x8000) {
            return delta - 0xFFFF;
        }
    } else if (delta < -0x8000) {
        return delta + 0xFFFF;
    }
    return delta;
}

void ai_measure_relative_point(MeasureEntity *entity, f32 *point, s32 *bodyDelta, s32 *headDelta)
    __asm__("func_800E28DC");

void ai_measure_relative_point(MeasureEntity *entity, f32 *point, s32 *bodyDelta, s32 *headDelta) {
    f32 dir[2];
    u16 headAngle;
    u16 bodyAngle;
    f32 length;
    u16 angle;

    dir[1] = point[1] - entity->x;
    dir[0] = point[0] - entity->z;
    headAngle = entity->value400 * (65536.0f / 360.0f);
    bodyAngle = entity->value3FC * (65536.0f / 360.0f);
    length = vec2_length(dir);
    angle = headAngle;
    if (!(length < 0.01f)) {
        dir[1] /= length;
        dir[0] /= length;
        if (dir[1] < 0.0f) {
            angle = -radians_to_angle(dir[0]);
        } else {
            angle = radians_to_angle(dir[0]);
        }
    }
    if (bodyDelta != 0) {
        *bodyDelta = wrap_angle_delta(-bodyAngle + angle);
    }
    if (headDelta != 0) {
        *headDelta = wrap_angle_delta(-headAngle + angle);
    }
}
