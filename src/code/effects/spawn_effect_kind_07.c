#include "types.h"

typedef struct EffectKind07 {
    u8 pad00[0xC];
    u8 variant;
    u8 pad0D;
    s16 value0E;
    f32 value10;
    f32 value14;
    u8 value18;
    u8 pad19[0x3];
    s32 spawnTick;
} EffectKind07;

extern EffectKind07 *allocate_effect_record(s32 group, s32 kind, s32 size) __asm__("func_8008AE18");
extern s32 gGameTicks __asm__("D_801B4AA8");

EffectKind07 *spawn_effect_kind_07(f32 value14, f32 value10, s16 value0E, u8 variant, u8 value18)
    __asm__("func_80078834");

EffectKind07 *spawn_effect_kind_07(f32 value14, f32 value10, s16 value0E, u8 variant, u8 value18)
{
    EffectKind07 *effect;

    effect = allocate_effect_record(1, 7, 0x24);
    if (effect == 0) {
        return 0;
    }
    effect->variant = variant;
    switch (variant) {
    case 0:
    case 2:
    case 3:
        effect->value0E = value0E;
        effect->value14 = value14;
        effect->value10 = value10;
        effect->value18 = value18;
        break;
    }
    effect->spawnTick = gGameTicks;
    return effect;
}
