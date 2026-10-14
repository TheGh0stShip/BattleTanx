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
extern u64 func_8007B268(void) __asm__("func_8007B268");
extern s16 func_800F38F4(void) __asm__("func_800F38F4");

s32 spawn_effect_kind_27(f32 *pos, f32 *params) __asm__("func_800EF020");

s32 spawn_effect_kind_27(f32 *pos, f32 *params) {
    EffectKind27 *e;
    f32 v;
    s16 s;
    u16 r;


    e = allocate_effect(1, 0x27, 0x40);
    if (e != 0) {
        e->templateIndex = 0;
        e->value2C = params[0];
        v = params[1];
        if (v < 0.0f) {
            v = -v;
        }
        e->value30 = v;
        e->value34 = params[2];
        e->value38 = 0.0f;
        e->value0D = 0;
        e->value0E = 1;
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
            e->value2A = 0xFF9C;
        } else {
            e->value2A = 100;
        }
    }
    return 1;
}
