#include "types.h"

typedef struct GlowColor {
    u8 red;
    u8 green;
    u8 blue;
    u8 alpha;
} GlowColor;

typedef struct GlowDef {
    u8 pad00[0x4];
    u16 duration;
    u8 pad06[0x8];
    u8 fromColor0;
    u8 toColor0;
    u8 fromColor1;
    u8 toColor1;
} GlowDef;

typedef struct GlowVec3 {
    f32 v[3];
} GlowVec3;

typedef struct GlowEffect {
    u8 pad00[0xC];
    u8 defIndex;
    u8 pad0D[0x7];
    u16 elapsed;
    u8 pad16[0x2];
    s32 scale;
    GlowVec3 position;
    u16 angle;
} GlowEffect;

typedef struct GlowGfx {
    u32 w0;
    u32 w1;
} GlowGfx;

extern GlowDef *gEffectParticleDefTable[] __asm__("D_80137940");
extern GlowColor *gEffectColorTable[] __asm__("D_80139048");
extern s16 D_802D5A7C;

extern void lerp_color(GlowColor *out, GlowColor *from, GlowColor *to, f32 t) __asm__("func_800AB24C");
extern s32 get_spawn_session(void) __asm__("func_800821C0");
extern void func_80084F90(s32 session, s16 id, GlowVec3 *position, s32 arg3, f32 scaleX, f32 scaleY, s32 angle,
                          GlowGfx *gfx, s32 gfxCount, f32 radius);

void draw_color_ramp_effect(GlowEffect *effect) __asm__("func_800EDE64");

void draw_color_ramp_effect(GlowEffect *record) {
    GlowEffect *effect = record;
    GlowGfx gfx[2];
    GlowColor primary;
    GlowColor environment;
    GlowDef *def;
    f32 t;
    f32 scale;
    s32 session;
    u32 duration;

    def = gEffectParticleDefTable[effect->defIndex];
    duration = def->duration;
    t = (f32)effect->elapsed / (f32)duration;
    lerp_color(&primary, gEffectColorTable[def->fromColor0], gEffectColorTable[def->toColor0], t);
    lerp_color(&environment, gEffectColorTable[def->fromColor1], gEffectColorTable[def->toColor1], t);
    gfx[0].w0 = 0xFA000000;
    gfx[0].w1 = (environment.red << 24) | (environment.green << 16) | (environment.blue << 8) | environment.alpha;
    gfx[1].w0 = 0xFB000000;
    gfx[1].w1 = (primary.red << 24) | (primary.green << 16) | (primary.blue << 8) | primary.alpha;
    session = get_spawn_session();
    scale = effect->scale * 0.8f;
    func_80084F90(session, D_802D5A7C, &effect->position, 0, scale, scale, effect->angle, gfx, 2, scale);
}
