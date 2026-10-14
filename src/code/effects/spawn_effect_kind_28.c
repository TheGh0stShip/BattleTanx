#include "types.h"

typedef struct EffectVec3 {
    f32 x;
    f32 y;
    f32 z;
} EffectVec3;

typedef struct SpawnTemplate28 {
    u8 pad00[0x8];
    s16 value08;
    s16 value0A;
    u16 flags;
} SpawnTemplate28;

typedef struct EffectKind28 {
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
    EffectVec3 pos;
    s16 value28;
    u16 value2A;
    s32 value2C;
    s32 value30;
    s32 value34;
    s32 value38;
} EffectKind28;

typedef struct EffectKind28Source {
    u8 pad00[0x18];
    EffectVec3 pos;
} EffectKind28Source;

extern SpawnTemplate28 *D_80137940[];
extern EffectKind28 *allocate_effect(s32 group, s32 kind, s32 size) __asm__("func_8008AD10");
extern u64 func_8007B268(void) __asm__("func_8007B268");
extern s16 func_800F38F4(void) __asm__("func_800F38F4");
extern void func_8008C2EC(EffectVec3 *pos, s16 arg1) __asm__("func_8008C2EC");

s32 spawn_effect_kind_28(EffectKind28Source *source, u32 templateAndX, u32 yAndZ) __asm__("func_800EE000");

s32 spawn_effect_kind_28(EffectKind28Source *source, u32 templateAndX, u32 yAndZ)
{
    EffectKind28 *e;
    u16 r;
    u32 y;

    e = allocate_effect(1, 0x28, 0x40);
    y = yAndZ >> 16;
    if (e != 0) {
        e->templateIndex = templateAndX >> 16;
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
        e->pos = source->pos;
        e->pos.x += (s16)templateAndX;
        e->pos.y += (s16)y;
        e->pos.z += (s16)yAndZ;
        e->value28 = func_800F38F4();
        e->value2A = 0;
        if (D_80137940[e->templateIndex]->flags & 0x10) {
            func_8008C2EC(&e->pos, D_80137940[e->templateIndex]->value0A);
        }
    }
    return 1;
}
