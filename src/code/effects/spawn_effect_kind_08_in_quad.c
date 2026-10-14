#include "types.h"

typedef struct Vec3f {
    f32 x;
    f32 y;
    f32 z;
} Vec3f;

typedef struct SpawnQuad {
    f32 x0;
    f32 z0;
    f32 x1;
    f32 z1;
    u8 pad10[0x8];
    f32 x3;
    f32 z3;
} SpawnQuad;

typedef struct EffectKind08 {
    u8 pad00[0xC];
    Vec3f pos;
    Vec3f vel;
    s16 rot[3];
    f32 scale;
    s32 value30;
    u8 value34;
    u8 pad35[3];
    s32 value38;
    f32 value3C;
} EffectKind08;

extern EffectKind08 *allocate_effect(s32 group, s32 kind, s32 size) __asm__("func_8008AD10");
extern f32 random_float_range(f32 range) __asm__("func_800F3880");
extern u32 random_u32(void) __asm__("func_800F38F4");
extern f32 angle_sin(u16 angle) __asm__("func_800F3AE0");
extern f32 angle_cos(u16 angle) __asm__("func_800F3B40");

void spawn_effect_kind_08_in_quad(SpawnQuad *quad, s32 count, u16 heading, f32 minY, f32 maxY, f32 scale, s32 arg6) __asm__("func_8008F248");

void spawn_effect_kind_08_in_quad(SpawnQuad *quad, s32 count, u16 heading, f32 minY, f32 maxY, f32 scale, s32 arg6) {
    Vec3f pos;
    Vec3f vel;
    f32 originX;
    f32 originZ;
    f32 edgeAX;
    f32 edgeAZ;
    f32 edgeBX;
    f32 edgeBZ;
    f32 u;
    f32 v;
    u16 rx;
    u16 ry;
    u16 rz;
    u16 angle;
    s32 i;
    EffectKind08 *e;

    originX = quad->z0;
    originZ = quad->x0;
    edgeAX = quad->z1 - originX;
    edgeAZ = quad->x1 - originZ;
    edgeBX = quad->z3 - originX;
    edgeBZ = quad->x3 - originZ;
    for (i = 0; i < count; i++) {
        pos.y = minY + random_float_range(maxY - minY);
        u = random_float_range(1.0f);
        v = random_float_range(1.0f);
        pos.x = originX + edgeAX * u + edgeBX * v;
        pos.z = originZ + edgeAZ * u + edgeBZ * v;
        rx = random_u32() % 0xFFFF;
        ry = random_u32() % 0xFFFF;
        rz = random_u32() % 0xFFFF;
        angle = heading + (random_u32() & 0xFFF) - 0x800;
        vel.x = angle_sin(angle) * 9.0f;
        vel.z = angle_cos(angle) * 9.0f;
        vel.y = random_float_range(4.5f) + 2.25f;
        e = allocate_effect(1, 8, 0x40);
        if (e != 0) {
            e->pos = pos;
            e->vel = vel;
            e->scale = scale;
            e->rot[0] = rx;
            e->rot[1] = ry;
            e->rot[2] = rz;
            e->value30 = arg6;
            e->value34 = 0;
            e->value38 = 0;
            e->value3C = 1.0f;
            e->vel.x *= scale;
            e->vel.y *= scale;
            e->vel.z *= scale;
        }
    }
}
