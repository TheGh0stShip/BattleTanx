#include "types.h"

typedef struct EffectKind0F {
    u8 pad00[0xC];
    f32 pos[3];
    f32 vel[3];
    s16 value24;
    s16 value26;
    s8 value28;
    u8 pad29[0x3];
    s32 value2C;
} EffectKind0F;

extern EffectKind0F *allocate_effect(s32 group, s32 kind, s32 size) __asm__("func_8008AD10");
extern f32 random_float_range(f32 range) __asm__("func_800F3880");
extern f32 angle_sin(u16 angle) __asm__("func_800F3AE0");
extern f32 angle_cos(u16 angle) __asm__("func_800F3B40");

extern f32 D_80074ED4;
extern f32 D_80074ED8;
extern f32 D_80074EDC;
extern f32 D_80074EE0;
extern f32 D_80074EE4;
extern f32 D_80074EE8;

s32 spawn_effect_kind_0f(f32 *pos, u16 angle, s8 value28, s32 value2C) __asm__("func_800F3344");

s32 spawn_effect_kind_0f(f32 *pos, u16 angle, s8 value28, s32 value2C) {
    EffectKind0F *effect = allocate_effect(1, 0xF, 0x30);
    f32 range;
    f32 scale;
    f32 base;
    f32 dir;
    f32 jitter;

    if (effect == 0) {
        return -1;
    }
    {
        range = D_80074ED4;
        effect->value28 = value28;
        dir = angle_sin(angle);
        scale = D_80074ED8;
        jitter = random_float_range(range);
        base = D_80074EDC;
        effect->vel[0] = dir * scale * (jitter + base);
        effect->vel[1] = (random_float_range(D_80074EE0) + D_80074EE4) * D_80074EE8;
        effect->vel[2] = angle_cos(angle) * scale * (random_float_range(range) + base);
        effect->pos[0] = pos[0];
        effect->pos[1] = pos[1];
        effect->pos[2] = pos[2];
        effect->value26 = 0;
        effect->value24 = 0x50;
        effect->value2C = value2C;
    }
    return 0;
}
