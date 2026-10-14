#include "types.h"

typedef struct EffectKind13 {
    u8 pad00[0xC];
    s32 value0C;
    s32 value10;
    s32 value14;
} EffectKind13;

extern EffectKind13 *allocate_effect(s32 group, s32 kind, s32 size) __asm__("func_8008AD10");

EffectKind13 *spawn_effect_kind_13(s32 value0C, s32 value10, s32 value14) __asm__("func_80091CA4");

EffectKind13 *spawn_effect_kind_13(s32 value0C, s32 value10, s32 value14)
{
    EffectKind13 *effect;

    effect = allocate_effect(0, 0x13, sizeof(EffectKind13));
    if (effect == 0) {
        return 0;
    }
    effect->value0C = value0C;
    effect->value10 = value10;
    effect->value14 = value14;
    return effect;
}
