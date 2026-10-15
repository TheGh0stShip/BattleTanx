#include "types.h"

typedef struct Vec3f {
    f32 x;
    f32 y;
    f32 z;
} Vec3f;

typedef struct DriftParticle {
    u8 pad00[0xC];
    Vec3f position;
    Vec3f velocity;
    u8 color[3];
} DriftParticle;

extern f32 random_float_range(f32 range) __asm__("func_800F3880");
extern void func_800F195C(Vec3f *origin, Vec3f *target, s32 arg2, s32 arg3, s32 byte0, s32 byte1, s32 byte2);

void drift_particle_update(DriftParticle *particle, s32 *state) __asm__("func_800F1CA0");

void drift_particle_update(DriftParticle *particle, s32 *state) {
    Vec3f next;

    particle->velocity.y -= 0.45f;
    next.x = particle->position.x + particle->velocity.x + random_float_range(24.0f) - 12.0f;
    next.y = particle->position.y + particle->velocity.y + random_float_range(24.0f) - 12.0f;
    next.z = particle->position.z + particle->velocity.z + random_float_range(24.0f) - 12.0f;
    func_800F195C(&particle->position, &next, 12, 1, particle->color[0], particle->color[1], particle->color[2]);
    particle->position = next;
    if (particle->position.y < 0.0f) {
        *state = 2;
    }
}
