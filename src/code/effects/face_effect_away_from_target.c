#include "types.h"

typedef struct HeadingEffect {
    u8 pad00[0xC];
    u8 flags;
    u8 pad0D[0x5];
    s16 target;
    u8 pad14[0xA];
    s16 heading;
} HeadingEffect;

typedef struct TargetPoint {
    u8 pad00[0x48];
    f32 x;
    f32 z;
    u8 pad50[0x8];
} TargetPoint;

typedef struct HeadingSession {
    u8 pad000[0x568];
    TargetPoint *points;
} HeadingSession;

typedef struct HeadingPos {
    f32 x;
    f32 z;
} HeadingPos;

extern float sqrtf(float);
extern HeadingSession *get_spawn_session(void) __asm__("func_800821C0");
extern s32 radians_to_angle(f32 radians) __asm__("func_800F3BE4");
extern void release_effect(HeadingEffect *effect) __asm__("func_8008B89C");

void face_effect_away_from_target(HeadingEffect *effect, s32 arg1, HeadingPos *pos) __asm__("func_8009390C");

void face_effect_away_from_target(HeadingEffect *effect, s32 arg1, HeadingPos *pos)
{
    TargetPoint *point;
    f32 dz;
    f32 dx;

    if (effect->flags & 4) {
        return;
    }
    effect->flags |= 3;
    point = &get_spawn_session()->points[effect->target];
    dz = pos->z - point->z;
    dx = pos->x - point->x;
    if ((dz != 0.0f) | (dx != 0.0f)) {
        effect->flags |= 8;
        if (-dz < 0.0f) {
            effect->heading = -radians_to_angle(-dx / sqrtf(dz * dz + dx * dx));
        } else {
            effect->heading = radians_to_angle(-dx / sqrtf(dz * dz + dx * dx));
        }
    }
    release_effect(effect);
}
