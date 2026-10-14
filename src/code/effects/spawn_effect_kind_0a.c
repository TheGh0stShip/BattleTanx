#include "types.h"

typedef struct EffectKind0A {
    u8 pad00[0xC];
    s32 value0C;
    f32 value10;
    f32 value14;
    f32 value18;
    s32 value1C;
} EffectKind0A;

extern EffectKind0A *allocate_effect(s32 group, s32 kind, s32 size) __asm__("func_8008AD10");
extern s32 audio_restarts_disabled(void) __asm__("func_800EC644");
extern f32 D_8007438C;

EffectKind0A *spawn_effect_kind_0a(f32 *pos, s32 arg) __asm__("func_800DD970");

EffectKind0A *spawn_effect_kind_0a(f32 *pos, s32 arg)
{
    EffectKind0A *effect;

    if (audio_restarts_disabled() != 0) {
        return 0;
    }
    effect = allocate_effect(1, 0xA, 0x20);
    if (effect == 0) {
        return 0;
    }
    effect->value0C = 0;
    effect->value14 = pos[1];
    effect->value10 = pos[0];
    effect->value1C = arg;
    effect->value18 = D_8007438C;
    return effect;
}
