#include "types.h"

typedef struct EffectVec3 {
    f32 x;
    f32 y;
    f32 z;
} EffectVec3;

typedef struct EffectOwner {
    s32 value00;
    s32 value04;
} EffectOwner;

typedef struct PositionEffect {
    u8 pad00[0xC];
    EffectVec3 pos;
    s16 value18;
    u8 pad1A[2];
    EffectOwner *owner;
    s32 value20;
    s32 value24;
} PositionEffect;

extern PositionEffect *allocate_effect(s32 group, s32 kind, s32 size) __asm__("func_8008AD10");

void spawn_attached_position_effect(EffectOwner *owner, EffectVec3 *pos, s16 value)
    __asm__("func_800F2630");

void spawn_attached_position_effect(EffectOwner *owner, EffectVec3 *pos, s16 value) {
    PositionEffect *effect = allocate_effect(1, 0x18, 0x28);

    if (effect != 0) {
        effect->pos = *pos;
        effect->value18 = value;
        effect->owner = owner;
        effect->value20 = owner->value04;
        effect->value24 = 0;
    }
}
