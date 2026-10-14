#include "types.h"

typedef struct ParticleColor {
    u8 red;
    u8 green;
    u8 blue;
    u8 alpha;
} ParticleColor;

typedef struct ParticleRenderDef {
    u8 pad00[0x4];
    u32 duration;
    u8 pad08[0x6];
    u8 fromColor0;
    u8 toColor0;
    u8 fromColor1;
    u8 toColor1;
} ParticleRenderDef;

typedef struct RenderedParticle {
    u8 pad00[0xC];
    u8 defIndex;
    u8 pad0D[0x7];
    u16 elapsed;
    u8 pad16[0x2];
    s32 scale;
    f32 position[3];
    u16 angleX;
    u16 angleY;
    u16 angleZ;
    u8 pad2E[0x6];
    s8 direction;
    u8 pad35[0x3];
    s16 fade;
} RenderedParticle;

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
extern f32 D_80074BD8;
extern f32 D_80074BDC;
extern s16 D_802D5ABE;
extern ParticleRenderDef *gEffectParticleDefTable[] __asm__("D_80137940");
extern ParticleColor *gEffectColorTable[] __asm__("D_80139048");

extern void lerp_color(ParticleColor *out, ParticleColor *from, ParticleColor *to, f32 t) __asm__("func_800AB24C");
extern void set_matrix_identity(f32 *matrix) __asm__("func_800A7650");
extern void load_render_translation(f32 *matrix, ParticleVec3 *vector) __asm__("func_800A76A0");
extern void scale_matrix_axes(f32 *matrix, f32 x, f32 y, f32 z) __asm__("func_800A823C");
extern void apply_render_matrix(f32 *matrix, ParticleMatrix *target, u16 angle) __asm__("func_800A841C");
extern void build_render_rotation(ParticleMatrix *target, f32 *matrix, u16 angle) __asm__("func_800A82B8");
extern s32 get_spawn_session(void) __asm__("func_800821C0");
extern void dispatch_nearby_sector_mask(s32 table, s32 a1, ParticleMatrix *a2, s32 a3, s32 a4, s32 a5,
                                        ParticleGfx *a6, s32 a7, f32 *pos, f32 radius) __asm__("func_80084DF4");

void draw_effect_particle(RenderedParticle *particle) __asm__("func_800EE8B4");

void draw_effect_particle(RenderedParticle *particle) {
    f32 matrix[16];
    ParticleMatrix transform;
    ParticleColor primary;
    ParticleColor environment;
    ParticleGfx gfx[2];
    ParticleVec3 position;
    f32 point[2];
    ParticleRenderDef *def;
    f32 t;
    f32 scale;
    s32 session;

    def = gEffectParticleDefTable[particle->defIndex];
    transform = D_80074B70;
    t = (f32)particle->elapsed / (f32)def->duration;
    if (particle->direction > 0) {
        lerp_color(&primary, gEffectColorTable[def->fromColor0], gEffectColorTable[def->toColor0], t);
        lerp_color(&environment, gEffectColorTable[def->fromColor1], gEffectColorTable[def->toColor1], t);
    } else {
        lerp_color(&primary, gEffectColorTable[def->toColor0], gEffectColorTable[def->fromColor0], t);
        lerp_color(&environment, gEffectColorTable[def->toColor1], gEffectColorTable[def->fromColor1], t);
    }
    if (particle->fade != 0) {
        environment.alpha = (30 - particle->fade * environment.alpha) / 30;
        primary.alpha = (30 - particle->fade * primary.alpha) / 30;
    }
    gfx[0].w0 = 0xFA000000;
    gfx[0].w1 = (environment.red << 24) | (environment.green << 16) | (environment.blue << 8) | environment.alpha;
    gfx[1].w0 = 0xFB000000;
    gfx[1].w1 = (primary.red << 24) | (primary.green << 16) | (primary.blue << 8) | primary.alpha;
    position = *(ParticleVec3 *)particle->position;
    set_matrix_identity(matrix);
    load_render_translation(matrix, &position);
    scale = particle->scale / D_80074BD8;
    scale_matrix_axes(matrix, scale, 1.0f, scale);
    apply_render_matrix(matrix, &transform, particle->angleX);
    build_render_rotation(&transform, matrix, particle->angleY);
    apply_render_matrix(matrix, &transform, particle->angleZ);
    session = get_spawn_session();
    point[1] = particle->position[0];
    point[0] = particle->position[2];
    dispatch_nearby_sector_mask(session, D_802D5ABE, &transform, 0, 3, 0, gfx, 2, point, D_80074BDC);
}
