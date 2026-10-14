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

typedef struct EffectKind29 {
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
    s16 value2A;
    s16 value2C;
    s16 value2E;
    s16 value30;
    s16 value32;
    s8 value34;
    u8 pad35;
    s16 value36;
    s16 value38;
} EffectKind29;

typedef struct SpawnSource {
    u8 pad00[0x18];
    Vec3f pos;
} SpawnSource;

extern SpawnTemplate *D_80137940[];
extern EffectKind29 *allocate_effect(s32 group, s32 kind, s32 size) __asm__("func_8008AD10");
extern s16 get_elapsed_game_ticks(void) __asm__("func_8007B1DC");
extern u16 next_random_u16(void) __asm__("func_800F38F4");
extern s32 create_effect_motion(EffectKind29 *effect, s32 x, s32 y, s32 minX, s32 maxX, s32 minY,
                                s32 maxY, s32 mode, s32 flags) __asm__("func_80106D18");
extern s8 D_8033B630;
extern s8 D_8033B631;

s32 spawn_effect_kind_29_at_offset(SpawnSource *src, u32 indexAndX, u32 yAndZ) __asm__("func_800EE4D4");

s32 spawn_effect_kind_29_at_offset(SpawnSource *src, u32 indexAndX, u32 yAndZ) {
    EffectKind29 *e;
    s16 t;
    u32 hi;

    hi = yAndZ >> 16;
    e = allocate_effect(1, 0x29, 0x40);
    if (e != 0) {
        e->templateIndex = indexAndX >> 16;
        e->value0D = 0;
        e->value0E = 0;
        e->value18 = D_80137940[e->templateIndex]->value08;
        t = get_elapsed_game_ticks();
        e->value10 = t;
        e->value12 = t;
        e->value14 = 0;
        e->pos = src->pos;
        e->pos.x += (s16)indexAndX;
        e->pos.y += (s16)hi;
        e->pos.z += (s16)yAndZ;
        if (e->pos.z < 0.0f) {
            D_8033B631 = 1;
        } else {
            D_8033B630 = 1;
        }
        e->value28 = next_random_u16();
        e->value2A = next_random_u16();
        e->value2C = next_random_u16();
        e->value2E = next_random_u16() * 0x157C / 65535 + 0x3872;
        e->value30 = next_random_u16() * 0x514 / 65535 + 0x1482;
        e->value32 = next_random_u16() * 0x15E / 65535 + 0x55F;
        e->value34 = 1;
        e->value38 = 30;
        e->value36 = e->value18;
        create_effect_motion(e, e->pos.x, e->pos.z, -50, 50, -50, 50, 0x400, 0);
    }
    return 1;
}
