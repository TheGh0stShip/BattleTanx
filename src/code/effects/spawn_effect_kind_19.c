#include "types.h"

typedef struct EffectKind19 {
    u8 pad00[0xC];
    s8 value0C;
    s8 value0D;
    s8 value0E;
    u8 pad0F;
    s32 value10;
    s32 value14;
    s32 value18;
} EffectKind19;

extern EffectKind19 *allocate_effect(s32 group, s32 kind, s32 size) __asm__("func_8008AD10");

void spawn_effect_kind_19(s8 value0C, s8 value0D, s8 value0E, s32 value10, s32 value18) __asm__("func_800F2E50");

void spawn_effect_kind_19(s8 value0C, s8 value0D, s8 value0E, s32 value10, s32 value18)
{
    EffectKind19 *effect;

    effect = allocate_effect(1, 0x19, sizeof(EffectKind19));
    if (effect != 0) {
        effect->value0C = value0C;
        effect->value0D = value0D;
        effect->value0E = value0E;
        effect->value10 = value10;
        effect->value14 = 0;
        effect->value18 = value18;
    }
}
