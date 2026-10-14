#include "types.h"

typedef struct EffectKind0E {
    u8 pad00[0xC];
    f32 value0C;
    f32 value10;
    f32 value14;
    f32 value18;
    f32 value1C;
    f32 value20;
    s16 value24;
    s16 value26;
    s8 value28;
    u8 pad29[0x3];
    s32 value2C;
    s32 value30;
} EffectKind0E;

extern f32 D_80074E70;
extern f32 D_80074E74;

extern EffectKind0E *allocate_effect(s32 group, s32 kind, s32 size) __asm__("func_8008AD10");
extern f32 angle_sin(u16 angle) __asm__("func_800F3AE0");
extern f32 angle_cos(u16 angle) __asm__("func_800F3B40");
extern s32 find_sound_instance(s32 soundId, s32 index) __asm__("func_800796F0");

s32 spawn_effect_kind_0e(f32 *position, u16 angle, s8 value28, s32 value2C) __asm__("func_800F29F0");

s32 spawn_effect_kind_0e(f32 *position, u16 angle, s8 value28, s32 value2C)
{
    EffectKind0E *effect;
    f32 scale;

    effect = allocate_effect(1, 0xE, 0x34);
    if (effect == 0) {
        return -1;
    }
    scale = D_80074E70;
    effect->value28 = value28;
    effect->value18 = angle_sin(angle) * scale;
    effect->value1C = D_80074E74;
    effect->value20 = angle_cos(angle) * scale;
    effect->value0C = position[0];
    effect->value10 = position[1];
    effect->value14 = position[2];
    effect->value24 = 0xC8;
    effect->value26 = 0;
    effect->value2C = value2C;
    effect->value30 = -1;
    find_sound_instance(0x14, 0);
    return 0;
}
