#include "types.h"

typedef struct SpawnTemplate {
    u8 pad00[8];
    s16 value08;
} SpawnTemplate;

typedef struct EffectKind27 {
    u8 pad00[0xC];
    u8 templateIndex;
    s8 value0D;
    s8 value0E;
    u8 pad0F;
    s16 value10;
    s16 value12;
    s16 value14;
    u8 pad16[2];
    s32 value18;
    f32 pos[3];
    s16 value28;
    u16 value2A;
    f32 value2C;
    f32 value30;
    f32 value34;
    f32 value38;
} EffectKind27;

extern SpawnTemplate *D_80137940[];
extern EffectKind27 *allocate_effect(s32, s32, s32) __asm__("func_8008AD10");
extern f32 random_float_range(f32 range) __asm__("func_800F3880");
extern f32 D_80074BF4;
extern f32 D_80074BF8;
extern f32 D_80074BFC;
extern f32 D_80074C00;
extern u64 func_8007B268(void) __asm__("func_8007B268");
extern s16 func_800F38F4(void) __asm__("func_800F38F4");

s32 spawn_scattered_effect_kind_27(f32 *pos, u8 templateIndex, s8 arg2) __asm__("func_800EF16C");

s32 spawn_scattered_effect_kind_27(f32 *pos, u8 templateIndex, s8 arg2) {
    EffectKind27 *e;
    f32 range;
    s16 s;
    u16 r;

    e = allocate_effect(1, 0x27, 0x40);
    if (e != 0) {
        range = D_80074BF4;
        e->templateIndex = templateIndex;
        e->value2C = random_float_range(range);
        if (func_800F38F4() & 1) {
            e->value2C = -e->value2C;
        }
        e->value30 = random_float_range(D_80074BF8) + D_80074BFC;
        e->value34 = random_float_range(range);
        if (func_800F38F4() & 1) {
            e->value34 = -e->value34;
        }
        e->value38 = D_80074C00;
        e->value0D = arg2;
        e->value0E = 0;
        e->value18 = D_80137940[e->templateIndex]->value08;
        r = (u32)func_8007B268() >> 16;
        e->value10 = r;
        e->value12 = r;
        e->value14 = 0;
        e->pos[0] = pos[0];
        e->pos[1] = pos[1];
        e->pos[2] = pos[2];
        s = func_800F38F4();
        e->value28 = s;
        if (s & 1) {
            e->value2A = 0xF830;
        } else {
            e->value2A = 0x7D0;
        }
    }
    return 1;
}
