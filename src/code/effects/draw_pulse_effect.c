#include "types.h"

typedef struct ParticleColor {
    u8 red;
    u8 green;
    u8 blue;
    u8 alpha;
} ParticleColor;

typedef struct CachedMatrix {
    f32 mf[4][4];
    u32 address;
} CachedMatrix;

typedef struct PulseEffect {
    u8 pad00[0xC];
    s32 farRange;
    f32 pos[3];
    u8 pad1C[8];
    f32 cosine;
    f32 sine;
    void *displayList;
    u8 state;
    u8 pad31;
    s16 growTicks;
    s16 holdTicks;
    s16 fadeTicks;
    f32 rate;
    u8 texture0;
    u8 texture1;
    u8 pulse;
    u8 pad3F;
    u16 alpha;
} PulseEffect;

typedef struct ViewPlayer {
    u8 pad000[0xFC];
    u16 perspNorm;
    u8 pad0FE[2];
    u8 projection[0x40];
} ViewPlayer;

extern ParticleColor D_80142C98;
extern ParticleColor D_80142C9C;
extern ParticleColor D_80142CA0;
extern ParticleColor D_80142CA4;
extern ParticleColor D_80142CA8;
extern ParticleColor D_80142CAC;

extern u8 *get_spawn_session(void) __asm__("func_800821C0");
extern void func_800A77D4(CachedMatrix *state, f32 x, f32 y, f32 z, f32 sine, f32 cosine);
extern void push_cached_matrix_overlay(CachedMatrix *matrix, u8 params) __asm__("func_8007E694");
extern s32 get_difficulty_level(void) __asm__("func_8007AAA0");
extern void push_overlay_display_list_variant(u16 variant) __asm__("func_800AA3D0");
extern void load_table_texture(u32 table, u16 index, s32 tile) __asm__("func_800AACCC");
extern void lerp_color(ParticleColor *out, ParticleColor *from, ParticleColor *to, f32 t) __asm__("func_800AB24C");
extern void set_env_color_overlay(void *arg0) __asm__("func_800A9EE0");
extern void set_primary_color_overlay(void *arg0) __asm__("func_800A9DA8");
extern s32 level_point_within_radius(void *level, s32 index, f32 x, f32 z) __asm__("func_8008332C");
extern s32 test_point_outside_sector(f32 x, f32 y, f32 r, void *point) __asm__("func_800941E0");
extern ViewPlayer *get_entity_record(u16 index) __asm__("func_800A6688");
extern u8 *func_800A424C(void *value);
extern void *func_800A42A4(void *value);
extern void append_display_list_call_1(void *displayList) __asm__("func_8007EF1C");
extern void push_cached_perspective_matrix(void *proj, u16 perspNorm) __asm__("func_8007E9C8");
extern void push_cached_matrix_load(void *matrix, u8 params) __asm__("func_8007E824");

void draw_pulse_effect(PulseEffect *effect) __asm__("func_8010BFDC");

void draw_pulse_effect(PulseEffect *effect)
{
    ParticleColor env;
    ParticleColor prim;
    ParticleColor *envFrom = &D_80142C98;
    ParticleColor *envTo = &D_80142C9C;
    ParticleColor *primFrom = &D_80142CA0;
    ParticleColor *primTo = &D_80142CA4;
    CachedMatrix matrix = { { { 1.0f, 0.0f, 0.0f, 0.0f },
                              { 0.0f, 1.0f, 0.0f, 0.0f },
                              { 0.0f, 0.0f, 1.0f, 0.0f },
                              { 0.0f, 0.0f, 0.0f, 1.0f } },
                            0 };
    f32 scale;
    f32 radius;
    u8 *session;
    u8 alpha;
    s32 count;
    s32 i;
    ViewPlayer *player;
    u8 *view;
    u16 perspNorm;
    u8 *proj;
    f32 *pos;
    s32 value;

    scale = 1.0f;
    alpha = 0xFF;
    session = get_spawn_session();
    switch (effect->state) {
    case 0:
        if (effect->growTicks-- > 0) {
            scale -= effect->growTicks * effect->rate;
        } else {
            f64 bias = 0.5;
            s32 n = 1;

            do {
                value = (s32)(n * (127.0f / effect->holdTicks) + bias);
                n += 2;
            } while (value < 2);
            effect->rate = value;
            effect->state = 1;
        }
        break;
    case 1:
        if (effect->holdTicks-- > 0) {
            s32 pulse = effect->pulse;

            /* sign mask shared with the hold-rate value above */
            value = (s32)(pulse << 24) >> 31;
            scale = ((pulse ^ value) & 0x7F) / 127.0f;
        } else {
            effect->state = 2;
            effect->rate = scale / effect->fadeTicks;
        }
        break;
    case 2:
        envFrom = &D_80142C9C;
        envTo = &D_80142CA8;
        primFrom = &D_80142CA4;
        primTo = &D_80142CAC;
        if (effect->fadeTicks-- > 0) {
            f32 prev = scale;

            scale -= effect->fadeTicks * effect->rate;
            alpha = (prev - scale) * 255.0f;
        } else {
            effect->state = 3;
            alpha = 0;
        }
        break;
    case 3:
        break;
    default:
        return;
    }
    func_800A77D4(&matrix, effect->pos[0], effect->pos[1], effect->pos[2], effect->sine, effect->cosine);
    push_cached_matrix_overlay(&matrix, 2);
    pos = effect->pos;
    count = get_difficulty_level();
    if (effect->state == 3) {
        return;
    }
    push_overlay_display_list_variant(1);
    if (effect->farRange == 0) {
        radius = 20.0f;
        load_table_texture(2, effect->texture0, 0);
        load_table_texture(2, effect->texture1, 1);
    } else {
        radius = 500.0f;
        load_table_texture(0, effect->texture0, 0);
        load_table_texture(0, effect->texture1, 1);
    }
    lerp_color(&env, envFrom, envTo, scale);
    env.alpha = alpha;
    lerp_color(&prim, primFrom, primTo, scale);
    prim.alpha = effect->alpha;
    set_env_color_overlay(&env);
    set_primary_color_overlay(&prim);
    for (i = 0; i < count; i++) {
        if (!level_point_within_radius(session, i, pos[0], pos[2])) {
            continue;
        }
        if (test_point_outside_sector(pos[0], pos[2], radius, session + 0x584 + i * 0x2C)) {
            continue;
        }
        player = get_entity_record(i);
        view = func_800A424C(player);
        perspNorm = player->perspNorm;
        proj = player->projection;
        append_display_list_call_1(func_800A42A4(player));
        push_cached_perspective_matrix(proj, perspNorm);
        push_cached_matrix_load(view + 0x48, 1);
        append_display_list_call_1(effect->displayList);
    }
}
