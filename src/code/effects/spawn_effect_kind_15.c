#include "types.h"

typedef struct EffectKind15 {
    u8 pad00[0xC];
    s8 value0C;
    s8 value0D;
    u8 pad0E[0x2];
    s32 value10;
    s8 value14;
    u8 pad15[0x3];
    s32 handle;
    f32 x;
    f32 y;
    u8 pad24[0x8];
    s32 value2C;
    struct EffectKind15 *next;
} EffectKind15;

typedef struct EffectPoint {
    f32 x;
    f32 y;
} EffectPoint;

extern EffectKind15 *allocate_effect(s32 group, s32 kind, s32 size) __asm__("func_8008AD10");
extern s32 create_effect_motion(EffectKind15 *effect, s32 x, s32 y, s32 minX, s32 maxX, s32 minY, s32 maxY,
                                s32 mode, s32 flags) __asm__("func_80106D18");
extern f32 D_80073050;
extern s32 D_801266F4;
extern EffectKind15 *D_802DF350;

EffectKind15 *spawn_effect_kind_15(s8 value, EffectPoint *position) __asm__("func_800A6958");

EffectKind15 *spawn_effect_kind_15(s8 value, EffectPoint *position) {
    EffectKind15 *effect;
    EffectKind15 *previous;
    EffectPoint corners[4];

    if (D_801266F4 == 0) {
        D_801266F4 = 1;
    }
    effect = allocate_effect(0, 0x15, 0x34);
    if (effect == 0) {
        return 0;
    }
    {
        effect->value0C = value;
        effect->value0D = value;
        effect->value10 = 0;
        effect->value14 = value;
        effect->value2C = 0;
        corners[0].y = position->y - D_80073050;
        corners[0].x = position->x - D_80073050;
        corners[1].y = position->y + D_80073050;
        corners[1].x = position->x - D_80073050;
        corners[2].y = position->y + D_80073050;
        corners[2].x = position->x + D_80073050;
        corners[3].y = position->y - D_80073050;
        corners[3].x = position->x + D_80073050;
        effect->handle = create_effect_motion(effect, (s32)position->y, (s32)position->x, -0x14, 0x14, -0x14,
                                              0x14, 2, 0);
        effect->y = position->y;
        previous = D_802DF350;
        effect->x = position->x;
        D_802DF350 = effect;
        effect->next = previous;
    }
    return effect;
}
