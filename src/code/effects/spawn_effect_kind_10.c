#include "types.h"

typedef struct EffectKind10 {
    u8 pad00[0xC];
    f32 x;
    f32 value10;
    f32 z;
    s16 value18;
    s16 value1A;
    u8 value1C;
    u8 pad1D[3];
    s32 handle;
    u8 value24;
} EffectKind10;

extern EffectKind10 *allocate_effect(s32 group, s32 kind, s32 size) __asm__("func_8008AD10");
extern s32 audio_restarts_disabled(void) __asm__("func_800EC644");
extern s32 func_80106D18(EffectKind10 *, s32, s32, s32, s32, s32, s32, s32, s32);
extern f32 D_800749F0;

void spawn_effect_kind_10(s32 arg0, s32 x, s32 z, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, u8 arg8)
    __asm__("func_800ECC1C");

void spawn_effect_kind_10(s32 arg0, s32 x, s32 z, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, u8 arg8)
{
    EffectKind10 *effect;

    effect = allocate_effect(0, 0x10, 0x2C);
    if (effect != 0) {
        effect->x = x;
        effect->value18 = arg0;
        effect->z = z;
        effect->value10 = D_800749F0;
        effect->value1A = audio_restarts_disabled() == 0 ? 5 : 0;
        effect->value1C = 0;
        effect->value24 = arg8;
        effect->handle = func_80106D18(effect, x, z, arg3, arg4, arg5, arg6, 0xF85F, (u16)arg7);
    }
}
