#include "types.h"

typedef struct EffectKind2DTriple {
    s32 value00;
    s32 value04;
    s32 value08;
} EffectKind2DTriple;

typedef struct EffectKind2DParams {
    EffectKind2DTriple value00;
    u16 value0C;
    u8 pad0E[0x2];
    s32 value10;
    u16 value14;
    u8 pad16[0x2];
    s32 value18;
    f32 value1C;
    f32 value20;
} EffectKind2DParams;

typedef struct EffectKind2D {
    u8 pad00[0xC];
    EffectKind2DTriple value0C;
    u16 value18;
    u8 pad1A[0x2];
    s32 value1C;
    u16 value20;
    u8 pad22[0x2];
    s32 value24;
    f32 value28;
    f32 value2C;
    u8 value30;
    u8 value31;
    s16 value32;
    u8 value34;
    u8 value35;
    s16 value36;
    s16 value38;
} EffectKind2D;

extern u32 D_80142CD0;

extern EffectKind2D *allocate_effect(s32 group, s32 kind, s32 size) __asm__("func_8008AD10");
extern u32 next_random_u32(void) __asm__("func_800F38F4");

s32 spawn_effect_kind_2d(EffectKind2DParams *params) __asm__("func_8010CB60");

s32 spawn_effect_kind_2d(EffectKind2DParams *params)
{
    EffectKind2D *effect;
    u8 phase;

    effect = allocate_effect(1, 0x2D, 0x3C);
    if (effect == 0) {
        return -1;
    }
    effect->value0C = params->value00;
    effect->value18 = params->value0C;
    effect->value1C = params->value10;
    effect->value20 = params->value14;
    effect->value24 = params->value18;
    effect->value28 = params->value1C;
    effect->value2C = params->value20;
    phase = next_random_u32() & 7;
    effect->value30 = phase;
    effect->value32 = 0x80;
    effect->value31 = (phase + 1) % D_80142CD0;
    effect->value34 = next_random_u32();
    effect->value35 = next_random_u32();
    effect->value36 = 0;
    effect->value38 = 0x80;
    return 0;
}
