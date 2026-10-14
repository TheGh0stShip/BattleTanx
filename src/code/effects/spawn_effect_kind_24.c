#include "types.h"

typedef struct EffectVec3 {
    f32 x;
    f32 y;
    f32 z;
} EffectVec3;

typedef struct EffectKind24 {
    u8 pad00[0xC];
    EffectVec3 value0C;
    EffectVec3 value18;
    s8 value24;
    s8 value25;
    u8 value26;
    u8 pad27;
} EffectKind24;

extern EffectKind24 *allocate_effect(s32 group, s32 kind, s32 size) __asm__("func_8008AD10");

s32 spawn_effect_kind_24(EffectVec3 *a, EffectVec3 *b, s32 arg2, s32 arg3, u8 arg4) __asm__("func_800F1DC4");

s32 spawn_effect_kind_24(EffectVec3 *a, EffectVec3 *b, s32 arg2, s32 arg3, u8 arg4)
{
    EffectKind24 *effect = allocate_effect(1, 0x24, 0x28);

    if (effect == 0) {
        return -1;
    }
    effect->value0C = *a;
    effect->value18 = *b;
    effect->value24 = arg2;
    effect->value25 = arg3;
    effect->value26 = arg4;
    return 0;
}
