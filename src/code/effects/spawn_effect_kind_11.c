#include "types.h"

typedef struct EffectKind11 {
    u8 pad00[0xC];
    s32 value0C;
} EffectKind11;

extern EffectKind11 *allocate_effect(s32 group, s32 kind, s32 size) __asm__("func_8008AD10");
extern void func_800E5328(s32 id, s32 arg) __asm__("func_800E5328");
extern s32 audio_restarts_disabled(void) __asm__("func_800EC644");
extern s16 D_8033AAE0;
extern s8 D_8033B44A;
extern s16 D_8033B44C;

EffectKind11 *spawn_effect_kind_11(u16 id, s32 arg) __asm__("func_800E66BC");

EffectKind11 *spawn_effect_kind_11(u16 id, s32 arg)
{
    EffectKind11 *effect;

    if (audio_restarts_disabled() != 0) {
        return 0;
    }
    effect = allocate_effect(1, 0xB, 0x10);
    if (effect == 0) {
        return 0;
    }
    func_800E5328(id, arg);
    D_8033B44A = 1;
    D_8033B44C = 0;
    D_8033AAE0 = 0;
    effect->value0C = 1;
    return effect;
}
