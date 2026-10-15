#include "types.h"

typedef struct Vec3 {
    f32 x;
    f32 y;
    f32 z;
} Vec3;

typedef struct EffectKind08 {
    u8 pad00[0xC];
    Vec3 position;
    Vec3 velocity;
    s16 value24;
    s16 value26;
    u16 value28;
    u8 pad2A[2];
    f32 scale;
    s32 value30;
    u8 value34;
    u8 pad35[3];
    s32 value38;
    f32 value3C;
} EffectKind08;

extern EffectKind08 *allocate_effect(s32 group, s32 kind, s32 size) __asm__("func_8008AD10");

extern u32 random_u32(void) __asm__("func_800F38F4");
extern f32 angle_sin(u16 angle) __asm__("func_800F3AE0");
extern f32 angle_cos(u16 angle) __asm__("func_800F3B40");

static inline s32 spawn_effect_kind_08(Vec3 *position, Vec3 *direction, s16 arg2, s16 arg3, u16 arg4, f32 scale, s32 arg6,
                         u8 arg7, f32 arg8, s32 arg9)
{
    EffectKind08 *effect;

    effect = allocate_effect(1, 8, 0x40);
    if (effect == 0) {
        return -1;
    }
    effect->position = *position;
    effect->velocity = *direction;
    effect->scale = scale;
    effect->value24 = arg2;
    effect->value26 = arg3;
    effect->value28 = arg4;
    effect->value30 = arg6;
    effect->value34 = arg7;
    effect->value38 = arg9;
    effect->value3C = arg8;
    effect->velocity.x *= scale;
    effect->velocity.y *= scale;
    effect->velocity.z *= scale;
    return 0;
}

void spawn_effect_kind_08_burst(Vec3 *position, s32 count, f32 scale, s32 arg3) __asm__("func_8008F040");

void spawn_effect_kind_08_burst(Vec3 *position, s32 count, f32 scale, s32 arg3) {
    Vec3 dir;
    f32 horizontal;
    u16 yaw;
    u16 pitch;
    u16 rx;
    u16 ry;
    u16 rz;
    s32 i;

    for (i = 0; i < count; i++) {
        yaw = random_u32() % 0xFFFF;
        pitch = random_u32() & 0x1FFF;
        horizontal = angle_sin(pitch);
        dir.x = horizontal * 9.0f * angle_cos(yaw);
        dir.y = angle_cos(pitch) * 9.0f;
        dir.z = horizontal * 9.0f * angle_sin(yaw);
        rx = random_u32() % 0xFFFF;
        ry = random_u32() % 0xFFFF;
        rz = random_u32() % 0xFFFF;
        spawn_effect_kind_08(position, &dir, rx, ry, rz, scale, arg3, 0, 1.0f, 0);
    }
}
