#include "types.h"

typedef struct Vec3f {
    f32 x;
    f32 y;
    f32 z;
} Vec3f;

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
    Vec3f pos;
    s16 value28;
    u16 value2A;
    s32 value2C;
    s32 value30;
    s32 value34;
    s32 value38;
} EffectKind27;

typedef struct SpawnSource {
    u8 pad00[0x18];
    Vec3f pos;
} SpawnSource;

extern SpawnTemplate *D_80137940[];
extern EffectKind27 *allocate_effect(s32, s32, s32) __asm__("func_8008AD10");
extern u64 func_8007B268(void) __asm__("func_8007B268");
extern s16 func_800F38F4(void) __asm__("func_800F38F4");

s32 spawn_effect_kind_27_at_offset(SpawnSource *src, s32 indexAndX, u32 yAndZ) __asm__("func_800EDB20");

s32 spawn_effect_kind_27_at_offset(SpawnSource *src, s32 indexAndX, u32 yAndZ) {
    EffectKind27 *e;
    s16 s;
    u16 r;
    u32 hi;

    hi = yAndZ >> 16;
    e = allocate_effect(1, 0x27, 0x40);
    if (e != 0) {
        e->templateIndex = indexAndX >> 16;
        e->value2C = 0;
        e->value30 = 0;
        e->value34 = 0;
        e->value38 = 0;
        e->value0D = 0;
        e->value0E = 0;
        e->value18 = D_80137940[e->templateIndex]->value08;
        r = (u32)func_8007B268() >> 16;
        e->value10 = r;
        e->value12 = r;
        e->value14 = 0;
        e->pos = src->pos;
        e->pos.x += (s16)indexAndX;
        e->pos.y += (s16)hi;
        e->pos.z += (s16)yAndZ;
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
