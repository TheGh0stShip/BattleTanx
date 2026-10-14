#include "types.h"

typedef struct EffectKind26Position {
    s32 value00;
    s32 value04;
    s32 value08;
} EffectKind26Position;

typedef struct EffectKind26 {
    u8 pad00[0xC];
    u8 variant;
    u8 pad0D;
    s16 value0E;
    s16 value10;
    s16 value12;
    u8 value14;
    u8 pad15[0x3];
    EffectKind26Position position;
} EffectKind26;

extern s32 D_80138FBC;

extern EffectKind26 *allocate_effect(s32 group, s32 kind, s32 size) __asm__("func_8008AD10");
extern u64 func_8007B268(void) __asm__("func_8007B268");

void spawn_effect_kind_26(EffectKind26Position *position, s32 variant) __asm__("func_800ED8C0");

void spawn_effect_kind_26(EffectKind26Position *position, s32 variant) {
    EffectKind26 *effect;
    u32 r;

    if (variant == 0x1C) {
        variant = D_80138FBC;
        D_80138FBC = (variant + 1) % 13;
    }
    effect = allocate_effect(1, 0x26, 0x24);
    if (effect != 0) {
        effect->variant = variant;
        effect->value14 = 0;
        r = (u32)func_8007B268() >> 16;
        effect->value0E = r;
        effect->value10 = r;
        effect->value12 = 0;
        effect->position = *position;
    }
}
