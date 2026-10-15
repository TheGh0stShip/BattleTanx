#include "types.h"

typedef struct Vec3 {
    f32 x;
    f32 y;
    f32 z;
} Vec3;

typedef struct StreakEffect {
    u8 pad00[0xC];
    Vec3 position;
    Vec3 end;
    f32 axisB[3];
    f32 axisA[3];
    u8 age;
    u8 life;
    u8 mode;
    u8 r;
    u8 g;
    u8 b;
} StreakEffect;

extern StreakEffect *allocate_effect(s32 group, s32 kind, s32 size) __asm__("func_8008AD10");
extern f32 sqrtf(f32 value);

void create_streak_effect(Vec3 *start, Vec3 *end, s32 life, u8 mode, u8 r, u8 g, u8 b) __asm__("func_800F195C");

void create_streak_effect(Vec3 *start, Vec3 *end, s32 life, u8 mode, u8 r, u8 g, u8 b) {
    StreakEffect *effect;
    Vec3 dir;
    f32 flat[2];
    f32 y;

    effect = allocate_effect(1, 0x23, 0x44);
    if (effect == 0) {
        return;
    }
    effect->position = *start;
    effect->end = *end;
    effect->age = effect->life = life;
    effect->mode = mode;
    effect->r = r;
    effect->g = g;
    effect->b = b;
    dir.x = effect->end.x - effect->position.x;
    dir.y = effect->end.y - effect->position.y;
    dir.z = effect->end.z - effect->position.z;
    {
        f32 length = sqrtf(dir.x * dir.x + dir.y * dir.y + dir.z * dir.z);

        if (length == 0.0f) {
            return;
        }
        dir.x /= length;
        dir.y /= length;
        dir.z /= length;
    }
    flat[1] = effect->end.x - effect->position.x;
    flat[0] = effect->end.z - effect->position.z;
    {
        f32 length = sqrtf(flat[1] * flat[1] + flat[0] * flat[0]);

        if (length == 0.0f) {
            return;
        }
        flat[1] /= length;
        flat[0] /= length;
        length = -flat[0];
        effect->axisB[1] = 0.0f;
        effect->axisB[0] = length;
        effect->axisB[2] = flat[1];
    }
    y = dir.y;
    {
        f32 length = sqrtf(1.0f - y * y);
        f32 x = -dir.x * y;

        effect->axisA[1] = length;
        effect->axisA[0] = x;
        effect->axisA[2] = -dir.z * y;
    }
}
