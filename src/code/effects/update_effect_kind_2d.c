#include "types.h"

typedef struct EffectKind2D {
    u8 pad00[0x24];
    s32 value24;
    u8 pad28[0x8];
    u8 value30;
    u8 value31;
    s16 value32;
    u8 value34;
    u8 value35;
    u16 value36;
    u16 value38;
} EffectKind2D;

extern u32 D_80142CD0;

extern u32 next_random_u32(void) __asm__("func_800F38F4");

void update_effect_kind_2d(EffectKind2D *effect) __asm__("func_8010CC44");

void update_effect_kind_2d(EffectKind2D *effect) {
    s32 timer;
    u16 phase;

    timer = effect->value24;
    if (timer != -1) {
        if (timer != 0) {
            effect->value24 = timer - 1;
        }
    }
    if (effect->value32 > 0) {
        effect->value32 -= next_random_u32() & 1;
        if (effect->value32 < 0) {
            effect->value32 = 0;
        }
    }
    effect->value34++;
    effect->value35++;
    phase = effect->value36 + effect->value38;
    effect->value36 = phase;
    if (phase >= 0x100) {
        effect->value30++;
        effect->value31++;
        effect->value30 = effect->value30 % D_80142CD0;
        effect->value36 = 0;
        effect->value31 = effect->value31 % D_80142CD0;
    }
}
