#include "types.h"

typedef struct EffectKind01 {
    u8 pad00[0xC];
    f32 x;
    f32 z;
    s16 value14;
    u8 pad16[2];
    s32 handle;
    s8 active;
} EffectKind01;

extern EffectKind01 *allocate_effect(s32 group, s32 kind, s32 size) __asm__("func_8008AD10");
extern s32 register_effect_area(EffectKind01 *effect, s32 x, s32 z, s32 arg3, s32 arg4, s32 arg5,
                                 f32 *corners) __asm__("func_80106D00");

void spawn_effect_kind_01(f32 x, f32 z, s16 value) __asm__("func_8008C8D0");
void spawn_effect_kind_01(f32 x, f32 z, s16 value) {
    f32 corners[8];
    EffectKind01 *effect;

    effect = allocate_effect(1, 1, 0x20);
    if (effect != 0) {
        effect->x = x;
        effect->z = z;
        effect->value14 = value;
        effect->active = 1;
        corners[1] = effect->x - 50.0f;
        corners[0] = effect->z - 50.0f;
        corners[3] = effect->x + 50.0f;
        corners[2] = effect->z - 50.0f;
        corners[5] = effect->x + 50.0f;
        corners[4] = effect->z + 50.0f;
        corners[7] = effect->x - 50.0f;
        corners[6] = effect->z + 50.0f;
        effect->handle = register_effect_area(effect, effect->x, effect->z, 0x32, 0xF85F, 0, corners);
    }
}
