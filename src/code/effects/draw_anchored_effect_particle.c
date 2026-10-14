#include "types.h"

typedef struct ParticleColor {
    u8 red;
    u8 green;
    u8 blue;
    u8 alpha;
} ParticleColor;

typedef struct ParticleRampDef {
    u8 pad00[0x4];
    u16 duration;
    u8 pad06[0x8];
    u8 fromColor0;
    u8 toColor0;
    u8 fromColor1;
    u8 toColor1;
} ParticleRampDef;

typedef struct ParticleGfx {
    u32 w0;
    u32 w1;
} ParticleGfx;

typedef struct ParticleAnchor {
    u8 pad000[0x18];
    s32 value18;
    u8 pad01C[0x8];
    f32 posX;
    u8 pad028[0x4];
    f32 posZ;
    u8 pad030[0x40C - 0x30];
    u8 model40C[4];
} ParticleAnchor;

typedef struct AnchoredParticle {
    u8 pad00[0xC];
    u8 defIndex;
    u8 pad0D[0x7];
    u16 elapsed;
    u8 pad16[0x26];
    ParticleAnchor *anchor;
} AnchoredParticle;

extern s16 D_802D5A30[];
extern ParticleRampDef *gEffectParticleDefTable[] __asm__("D_80137940");
extern ParticleColor *gEffectColorTable[] __asm__("D_80139048");

extern void lerp_color(ParticleColor *out, ParticleColor *from, ParticleColor *to, f32 t) __asm__("func_800AB24C");
extern s32 get_spawn_session(void) __asm__("func_800821C0");
extern void refresh_entity_target(ParticleAnchor *entity) __asm__("func_8009D4B4");
extern void dispatch_nearby_sector_mask(s32 table, s32 a1, void *a2, s32 a3, s32 a4, s32 a5,
                                        ParticleGfx *a6, s32 a7, f32 *pos, f32 radius) __asm__("func_80084DF4");

void draw_anchored_effect_particle(AnchoredParticle *particle) __asm__("func_800EEE58");

void draw_anchored_effect_particle(AnchoredParticle *particle) {
    AnchoredParticle *self;
    ParticleColor primary;
    ParticleColor environment;
    f32 point[2];
    ParticleGfx gfx[2];
    ParticleRampDef *def;
    ParticleAnchor *anchor;
    s16 *model;
    s16 *models;
    f32 t;
    u32 duration;
    s32 session;

    self = particle;
    def = gEffectParticleDefTable[particle->defIndex];
    duration = def->duration;
    t = (f32)particle->elapsed / (f32)duration;
    lerp_color(&primary, gEffectColorTable[def->fromColor0], gEffectColorTable[def->toColor0], t);
    lerp_color(&environment, gEffectColorTable[def->fromColor1], gEffectColorTable[def->toColor1], t);
    gfx[0].w0 = 0xFA000000;
    gfx[0].w1 = (environment.red << 24) | (environment.green << 16) | (environment.blue << 8) | environment.alpha;
    gfx[1].w0 = 0xFB000000;
    gfx[1].w1 = (primary.red << 24) | (primary.green << 16) | (primary.blue << 8) | primary.alpha;
    session = get_spawn_session();
    anchor = self->anchor;
    point[1] = anchor->posX;
    point[0] = anchor->posZ;
    refresh_entity_target(anchor);
    models = D_802D5A30;
    if (anchor->value18 != 0) {
        model = &models[0x46];
    } else {
        model = &models[0x45];
    }
    dispatch_nearby_sector_mask(session, *model, anchor->model40C, 0, 4, 0, gfx, 2, point, 150.0f);
}
