#include "types.h"

typedef struct EffectTransform {
    f32 m[4][4];
    s32 value40;
} EffectTransform;

typedef struct OrientedEffect {
    u8 pad00[0xC];
    f32 position[3];
    u8 pad18[0xC];
    u16 roll;
    u16 pitch;
    u16 yaw;
    u8 pad2A[0x6];
    s32 modelIndex;
    u8 pad34[0x4];
    s32 value38;
    f32 scale;
} OrientedEffect;

extern EffectTransform D_80071C04;
extern f64 D_80071C48;
extern s16 D_802D5A30[];

extern s32 func_800821C0(void);
extern void func_80084A74(s32 world, s32 model, EffectTransform *transform, s32 mode, s32 a4, f32 *xz);
extern void set_euler_rotation(EffectTransform *m, u16 yaw, u16 pitch, u16 roll) __asm__("func_800A7800");
extern void func_800A76A0(EffectTransform *m, f32 *position);
extern void func_800A823C(EffectTransform *m, f32 x, f32 y, f32 z);

void submit_oriented_effect_model(OrientedEffect *effect) __asm__("func_8008EE04");

void submit_oriented_effect_model(OrientedEffect *effect) {
    f32 xz[2];
    EffectTransform transform;
    s32 world;

    transform = D_80071C04;
    world = func_800821C0();
    set_euler_rotation(&transform, effect->yaw, effect->pitch, effect->roll);
    func_800A76A0(&transform, effect->position);
    if (effect->scale != D_80071C48) {
        func_800A823C(&transform, effect->scale, effect->scale, effect->scale);
    }
    xz[1] = effect->position[0];
    xz[0] = effect->position[2];
    func_80084A74(world, D_802D5A30[effect->modelIndex], &transform, 3, effect->value38, xz);
}
