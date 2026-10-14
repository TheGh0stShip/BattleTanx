#include "types.h"

typedef struct Vec3f {
    f32 x;
    f32 y;
    f32 z;
} Vec3f;

typedef struct BounceParticleDef {
    u8 pad00[0x4];
    u16 duration;
    u8 pad06[0x2];
    s16 scaleFrom;
    s16 scaleTo;
    u16 flags;
} BounceParticleDef;

typedef struct BounceAnchor {
    u8 pad000[0x40C];
    u8 matrix[0x30];
} BounceAnchor;

typedef struct BounceParticle {
    u8 pad00[0xC];
    u8 defIndex;
    u8 cycle;
    u8 pad0E[0x2];
    u16 startTime;
    u16 now;
    u16 elapsed;
    u8 pad16[0x2];
    s32 scale;
    Vec3f pos;
    u16 angle;
    s16 spin;
    Vec3f vel;
    f32 gravity;
    BounceAnchor *anchor;
} BounceParticle;

extern BounceParticleDef *gEffectParticleDefTable[] __asm__("D_80137940");
extern u64 func_8007B268(void) __asm__("func_8007B268");
extern void transform_point_3x4(void *matrix, Vec3f *input, Vec3f *output) __asm__("func_800A7D10");
extern u32 next_random_u32(void) __asm__("func_800F38F4");

void update_bouncing_effect_particle(BounceParticle *particle, s32 *state) __asm__("func_800EDC64");

void update_bouncing_effect_particle(BounceParticle *particle, s32 *state) {
    BounceParticleDef *def;
    Vec3f offset;
    u32 now;
    u16 elapsed;
    u32 duration;
    f32 rate;

    def = gEffectParticleDefTable[particle->defIndex];
    now = (u32)func_8007B268() >> 16;
    particle->now = now;
    elapsed = now - particle->startTime;
    particle->elapsed = elapsed;
    duration = def->duration;
    if (elapsed <= duration) {
        rate = (f32)(def->scaleTo - def->scaleFrom) / (f32)duration;
        particle->scale = def->scaleFrom + elapsed * rate;
        particle->pos.x += particle->vel.x;
        particle->angle += particle->spin;
        particle->pos.y += particle->vel.y;
        particle->pos.z += particle->vel.z;
        particle->vel.y += particle->gravity;
        if (def->flags & 0x80) {
            BounceAnchor *anchor = particle->anchor;

            offset.x = 0.0f;
            offset.z = 95.0f;
            offset.y = 40.0f;
            transform_point_3x4(anchor->matrix, &offset, &particle->pos);
        }
        if ((def->flags & 1) && particle->pos.y <= particle->scale) {
            particle->pos.y = particle->scale;
            particle->vel.y = -particle->vel.y / 2.0f;
            if (next_random_u32() & 1) {
                particle->spin = -particle->spin;
            }
        }
    } else if (def->flags & 0x100) {
        particle->elapsed = 0;
        particle->cycle++;
        particle->defIndex++;
        particle->startTime = particle->now;
    } else {
        *state = 2;
    }
}
