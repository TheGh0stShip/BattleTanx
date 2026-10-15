#include "types.h"

typedef struct EffectKind01 {
    u8 pad00[0xC];
    f32 x;
    f32 z;
    u16 heading;
    u8 pad16[2];
    s32 handle;
    u8 active;
} EffectKind01;

extern EffectKind01 *allocate_effect(s32 group, s32 kind, s32 size) __asm__("func_8008AD10");
extern s32 register_effect_area(EffectKind01 *effect, s32 x, s32 z, s32 arg3, s32 arg4, s32 arg5,
                                 f32 *corners) __asm__("func_80106D00");
extern void move_effect_area(s32 handle, s32 x, s32 z, s32 radius, s32 arg4, f32 *corners) __asm__("func_80106D08");
extern void free_effect_area(s32 handle) __asm__("func_80107170");
extern f32 sinf_u16(u16 angle) __asm__("func_800F3AE0");
extern f32 cosf_u16(u16 angle) __asm__("func_800F3B40");
extern f32 random_float_range(f32 range) __asm__("func_800F3880");

void spawn_effect_kind_01(f32 x, f32 z, s16 value) __asm__("func_8008C8D0");

inline void spawn_effect_kind_01(f32 x, f32 z, s16 value) {
    f32 corners[8];
    EffectKind01 *effect;

    effect = allocate_effect(1, 1, 0x20);
    if (effect != 0) {
        effect->x = x;
        effect->z = z;
        effect->heading = value;
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

void update_effect_kind_01(EffectKind01 *effect, s32 *state) __asm__("func_8008C9E4");

/* Drifts along its heading, wraps at the arena edge, and occasionally splits into two diverging copies. */

void update_effect_kind_01(EffectKind01 *effect, s32 *state) {
    f32 corners[8];

    if (effect->active == 0) {
        *state = 1;
    } else {
        effect->x += sinf_u16(effect->heading) * 50.0f;
        effect->z += cosf_u16(effect->heading) * 50.0f;
        if (effect->x < -3000.0f) {
            effect->x += 6000.0f;
        }
        if (effect->x > 3000.0f) {
            effect->x -= 6000.0f;
        }
        if (effect->z < -3000.0f) {
            effect->z += 6000.0f;
        }
        if (effect->z > 3000.0f) {
            effect->z -= 6000.0f;
        }
        if (effect->handle >= 0) {
            corners[1] = effect->x - 50.0f;
            corners[0] = effect->z - 50.0f;
            corners[3] = effect->x + 50.0f;
            corners[2] = effect->z - 50.0f;
            corners[5] = effect->x + 50.0f;
            corners[4] = effect->z + 50.0f;
            corners[7] = effect->x - 50.0f;
            corners[6] = effect->z + 50.0f;
            move_effect_area(effect->handle, effect->x, effect->z, 0x32, 0, corners);
        }
        if (!(random_float_range(1000.0f) < 2.0)) {
            return;
        }
        *state = 2;
        spawn_effect_kind_01(effect->x, effect->z, effect->heading + 0x1020);
        spawn_effect_kind_01(effect->x, effect->z, effect->heading - 0x1020);
    }
    if (effect->handle >= 0) {
        free_effect_area(effect->handle);
    }
}
