#include "types.h"

typedef struct ParticleSweepDef {
    u8 pad00[4];
    u32 duration;
    s16 from;
    s16 to;
} ParticleSweepDef;

typedef struct OscillatingParticle {
    u8 pad00[0xC];
    u8 defIndex;
    u8 pad0D[3];
    u16 startTick;
    u16 currentTick;
    u16 elapsed;
    u8 pad16[2];
    s32 value;
    u8 pad1C[0xC];
    u16 value28;
    u16 value2A;
    u16 value2C;
    u16 value2E;
    u16 value30;
    u16 value32;
    s8 direction;
    u8 pad35;
    s16 base;
    s16 delay;
} OscillatingParticle;

extern s32 get_elapsed_game_ticks(void) __asm__("func_8007B1DC");
extern ParticleSweepDef *gEffectParticleDefTable[] __asm__("D_80137940");

void update_effect_particle_oscillation(OscillatingParticle *particle) __asm__("func_800EE75C");

void update_effect_particle_oscillation(OscillatingParticle *particle) {
    ParticleSweepDef *def = gEffectParticleDefTable[particle->defIndex];
    u16 tick = get_elapsed_game_ticks();

    particle->currentTick = tick;
    particle->elapsed = tick - particle->startTick;
    if (particle->delay != 0) {
        particle->delay--;
    }
    if (def->duration >= particle->elapsed) {
        f32 step = (particle->direction * (f32)(def->to - def->from)) / (f32)def->duration;

        particle->value = particle->base + particle->elapsed * step;
    } else {
        u16 now = particle->currentTick;
        s32 direction;

        particle->elapsed = 0;
        direction = -particle->direction;
        particle->direction = direction;
        particle->startTick = now;
        if ((s8)direction > 0) {
            particle->base = def->from;
        } else {
            particle->base = def->to;
        }
    }
    particle->value28 += particle->value2E;
    particle->value2A += particle->value30;
    particle->value2C += particle->value32;
}
