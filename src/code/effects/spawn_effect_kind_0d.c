#include "types.h"

typedef struct EffectKind0D {
    u8 pad00[0xC];
    f32 value0C;
    f32 value10;
    f32 value14;
    s16 value18;
    s8 value1A;
    u8 pad1B;
    s16 value1C;
    u8 pad1E[2];
    s32 value20;
    s32 value24;
    s32 value28;
    s8 value2C;
    u8 pad2D[3];
} EffectKind0D;

extern EffectKind0D *allocate_effect(s32 group, s32 kind, s32 size) __asm__("func_8008AD10");

s32 spawn_effect_kind_0d(f32 *pos, s16 value18, s8 value1A, s16 value1C, s32 value20, s32 value24,
                         s32 value28, s32 value2C) __asm__("func_800F15A0");

s32 spawn_effect_kind_0d(f32 *pos, s16 value18, s8 value1A, s16 value1C, s32 value20, s32 value24,
                         s32 value28, s32 value2C)
{
    EffectKind0D *effect;

    effect = allocate_effect(1, 0xD, sizeof(EffectKind0D));
    if (effect == 0) {
        return -1;
    }
    effect->value0C = pos[0];
    effect->value10 = pos[1];
    effect->value14 = pos[2];
    effect->value18 = value18;
    effect->value1A = value1A;
    effect->value1C = value1C;
    effect->value20 = value20;
    effect->value24 = value24;
    effect->value28 = value28;
    effect->value2C = value2C;
    return 1;
}
