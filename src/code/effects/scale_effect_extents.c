#include "types.h"

typedef struct EffectExtents {
    u8 pad00[0x6];
    s16 value06;
    s16 value08;
    s16 value0A;
    s16 value0C;
    s16 value0E;
} EffectExtents;

extern f32 D_80071E9C;

void scale_effect_extents(EffectExtents *effect) __asm__("func_8009249C");

void scale_effect_extents(EffectExtents *effect)
{
    f32 scale;

    scale = D_80071E9C;
    effect->value06 = (s32)(effect->value06 * scale);
    effect->value08 = (s32)(effect->value08 * scale);
    effect->value0A = (s32)(effect->value0A * scale);
    effect->value0C = (s32)(effect->value0C * scale);
    effect->value0E = (s32)(effect->value0E * scale);
}
