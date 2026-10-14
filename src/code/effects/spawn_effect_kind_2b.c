#include "types.h"

typedef struct EffectVec3 {
    f32 x;
    f32 y;
    f32 z;
} EffectVec3;

typedef struct EffectKind2B {
    u8 pad00[0xC];
    s32 value0C;
    EffectVec3 position;
    s32 lifetime;
    u16 value20;
    u16 value22;
    f32 value24;
    f32 value28;
    s32 value2C;
    u8 mode;
    u8 pad31;
    s16 value32;
    u16 value34;
    u16 value36;
    f32 drift;
    u8 currentIndex;
    u8 nextIndex;
    u8 value3E;
    u8 value3F;
    u16 blend;
    u16 blendStep;
} EffectKind2B;

typedef struct EffectKind2BParams {
    s32 value00;
    EffectVec3 position;
    f32 value10;
    f32 value14;
    s32 value18;
    s32 lifetime;
    u16 value20;
    u16 value22;
    u16 value24;
    u16 value26;
    u16 value28;
} EffectKind2BParams;

extern EffectKind2B *allocate_effect(s32 group, s32 kind, s32 size) __asm__("func_8008AD10");
extern u32 next_random_u32(void) __asm__("func_800F38F4");
extern f32 D_80075510;
extern f32 D_80075518;
extern u16 D_80142B70[];

EffectKind2B *spawn_effect_kind_2b(EffectKind2BParams *params) __asm__("func_8010BDA0");

EffectKind2B *spawn_effect_kind_2b(EffectKind2BParams *params)
{
    EffectKind2B *effect;
    u8 index;

    effect = allocate_effect(1, 0x2B, 0x44);
    if (effect == 0) {
        return 0;
    }
    effect->value0C = params->value00;
    effect->position = params->position;
    effect->value28 = params->value10;
    effect->value24 = params->value14;
    effect->value2C = params->value18;
    effect->lifetime = params->lifetime;
    effect->value20 = params->value20;
    effect->value22 = (u32)(params->value22 * D_80075510);
    effect->value32 = params->value24;
    effect->value34 = params->value26;
    effect->value36 = params->value28;
    effect->drift = D_80075518 / effect->value32;
    effect->mode = 0;
    index = next_random_u32() & 7;
    effect->currentIndex = index;
    effect->nextIndex = D_80142B70[index];
    effect->value3E = next_random_u32();
    effect->value3F = next_random_u32();
    effect->blend = 0;
    effect->blendStep = 0x40;
    return effect;
}
