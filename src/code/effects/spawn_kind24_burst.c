#include "types.h"

typedef struct {
    f32 x;
    f32 y;
    f32 z;
} EffectVec3;

typedef struct {
    u8 pad00[0xC];
    EffectVec3 position;
    EffectVec3 velocity;
    s8 color[3];
} EffectKind24;

extern EffectKind24 *allocate_effect(s32 group, s32 kind, s32 size) __asm__("func_8008AD10");
extern u32 random_u32(void) __asm__("func_800F38F4");
extern f32 angle_sin(u16 angle) __asm__("func_800F3AE0");
extern f32 angle_cos(u16 angle) __asm__("func_800F3B40");
extern f64 D_80074DF8;

void spawn_kind24_burst(EffectVec3 *origin) __asm__("func_800F1E74");

void spawn_kind24_burst(EffectVec3 *origin) {
    EffectVec3 velocity;
    EffectKind24 *effect;
    f64 scale;
    f32 sinPitch;
    u16 yaw;
    u16 pitch;
    s8 red;
    s8 green;
    s8 blue;
    s32 i;

    scale = D_80074DF8;
    for (i = 1; i < 7; i++) {
        yaw = random_u32() % 65535;
        pitch = random_u32() & 0x1FFF;
        sinPitch = angle_sin(pitch);
        velocity.x = sinPitch * scale * angle_sin(yaw);
        velocity.y = angle_cos(pitch) * scale;
        velocity.z = sinPitch * scale * angle_cos(yaw);
        red = (i & 1) ? -6 : 0;
        green = (i & 2) ? -6 : 0;
        blue = (i & 4) ? -6 : 0;
        effect = allocate_effect(1, 0x24, 0x28);
        if (effect != 0) {
            effect->position = *origin;
            effect->velocity = velocity;
            effect->color[0] = red;
            effect->color[1] = green;
            effect->color[2] = blue;
        }
    }
}
