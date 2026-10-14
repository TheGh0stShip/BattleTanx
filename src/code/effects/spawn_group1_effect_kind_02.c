#include "types.h"

typedef struct EffectG1Kind02 {
    u8 pad00[0xC];
    f32 value0C;
    f32 value10;
    f32 value14;
    f32 value18;
    f32 value1C;
    f32 value20;
    f32 value24;
    s16 value28;
    s16 value2A;
    u8 value2C;
    u8 value2D;
    u16 value2E;
    u16 value30;
    u8 value32;
    u8 pad33;
    s32 value34;
} EffectG1Kind02;

extern EffectG1Kind02 *allocate_effect(s32 group, s32 kind, s32 size) __asm__("func_8008AD10");

s32 spawn_group1_effect_kind_02(f32 *pos, f32 *pairA, f32 *pairB, s16 value28, u8 value2D,
                                u8 value2C, u16 value2E, u16 value30, s32 value34, u8 value32)
    __asm__("func_8008D660");

s32 spawn_group1_effect_kind_02(f32 *pos, f32 *pairA, f32 *pairB, s16 value28, u8 value2D,
                                u8 value2C, u16 value2E, u16 value30, s32 value34, u8 value32)
{
    EffectG1Kind02 *effect;

    effect = allocate_effect(1, 2, sizeof(EffectG1Kind02));
    if (effect == 0) {
        return -1;
    }
    effect->value32 = value32;
    effect->value2E = value2E;
    effect->value30 = value30;
    effect->value0C = pos[0];
    effect->value10 = pos[1];
    effect->value14 = pos[2];
    effect->value1C = pairA[1];
    effect->value18 = pairA[0];
    effect->value24 = pairB[1];
    effect->value20 = pairB[0];
    effect->value2C = value2C;
    effect->value28 = value28;
    effect->value2A = 0x70;
    effect->value2D = value2D;
    effect->value34 = value34;
    return 0;
}
