#include "types.h"

typedef struct ParticleColor {
    u8 red;
    u8 green;
    u8 blue;
    u8 alpha;
} ParticleColor;

typedef struct FlatParticleDef {
    u8 pad00[4];
    u16 duration;
    u8 pad06[8];
    u8 fromColor0;
    u8 toColor0;
    u8 fromColor1;
    u8 toColor1;
} FlatParticleDef;

typedef struct FlatParticle {
    u8 pad00[0xC];
    u8 defIndex;
    u8 pad0D[7];
    u16 elapsed;
    u8 pad16[2];
    s32 scale;
    f32 position[3];
} FlatParticle;

typedef struct ParticleMatrix {
    f32 m[17];
} ParticleMatrix;

typedef struct ParticleVec3 {
    f32 v[3];
} ParticleVec3;

typedef struct ParticleGfx {
    u32 w0;
    u32 w1;
} ParticleGfx;

extern ParticleMatrix D_80074B70;
extern s16 D_802D5ABE;
extern FlatParticleDef *gFlatParticleDefTable[] __asm__("D_80137940");
extern ParticleColor *gEffectColorTable[] __asm__("D_80139048");

void lerp_color(ParticleColor *out, ParticleColor *from, ParticleColor *to,
                f32 t) __asm__("func_800AB24C");
void load_render_translation(ParticleMatrix *matrix, ParticleVec3 *vector)
    __asm__("func_800A76A0");
void scale_matrix_axes(ParticleMatrix *matrix, f32 x, f32 y, f32 z)
    __asm__("func_800A823C");
s32 get_spawn_session(void) __asm__("func_800821C0");
void func_80084F4C(s32 session, s32 kind, ParticleMatrix *matrix, s32 arg3,
                   s32 arg4, s32 arg5, ParticleGfx *gfx, s32 count, f32 z,
                   f32 x);

void draw_flat_effect_particle(FlatParticle *particle)
    __asm__("func_800EE28C");

void draw_flat_effect_particle(FlatParticle *particle)
{
    ParticleMatrix transform;
    ParticleColor primary;
    ParticleColor environment;
    ParticleGfx gfx[2];
    ParticleVec3 position;
    FlatParticleDef *def;
    f32 t;
    f32 scale;
    u32 duration;
    s32 session;
    f32 x;
    f32 z;
    ParticleMatrix *matrix;

    def = gFlatParticleDefTable[particle->defIndex];
    transform = D_80074B70;
    duration = def->duration;
    t = (f32)particle->elapsed / (f32)duration;
    lerp_color(&primary, gEffectColorTable[def->fromColor0],
               gEffectColorTable[def->toColor0], t);
    lerp_color(&environment, gEffectColorTable[def->fromColor1],
               gEffectColorTable[def->toColor1], t);
    gfx[0].w0 = 0xFA000000;
    gfx[0].w1 = (environment.red << 24) | (environment.green << 16) |
                (environment.blue << 8) | environment.alpha;
    gfx[1].w0 = 0xFB000000;
    gfx[1].w1 = (primary.red << 24) | (primary.green << 16) |
                (primary.blue << 8) | primary.alpha;
    get_spawn_session();
    position = *(ParticleVec3 *)particle->position;
    matrix = &transform;
    load_render_translation(matrix, &position);
    scale = particle->scale / 1024.0f;
    scale_matrix_axes(matrix, scale, 1.0f, scale);
    session = get_spawn_session();
    x = position.v[0];
    z = position.v[2];
    func_80084F4C(session, D_802D5ABE, matrix, 0, 3, 0, gfx, 2, z, x);
}
