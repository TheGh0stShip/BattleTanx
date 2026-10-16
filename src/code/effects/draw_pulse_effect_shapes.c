#include "types.h"

typedef struct ParticleColor {
    u8 red;
    u8 green;
    u8 blue;
    u8 alpha;
} ParticleColor;

typedef struct PulseEffect {
    u8 pad00[0xC];
    u32 shape;
    f32 pos[3];
    u8 pad1C[4];
    u16 width;
    u16 height;
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
    u8 pulse0;
    u8 pulse1;
    u16 alpha;
} PulseEffect;

typedef struct ViewPlayer {
    u8 pad000[0xFC];
    u16 perspNorm;
    u8 pad0FE[2];
    u8 projection[0x40];
} ViewPlayer;

extern f32 D_80142B80[][3];
extern s32 D_80142BE0[4][4];
extern f32 D_80142C20[][3];
extern s32 D_80142C68[3][4];
extern ParticleColor D_80142CB0;
extern ParticleColor D_80142CB4;
extern ParticleColor D_80142CB8;
extern ParticleColor D_80142CBC;

extern s32 get_difficulty_level(void) __asm__("func_8007AAA0");
extern void push_overlay_display_list_variant(u16 variant) __asm__("func_800AA3D0");
extern void load_table_texture(u32 table, u16 index, s32 tile) __asm__("func_800AACCC");
extern void func_8007EB04(s32 mode);
extern void lerp_color(ParticleColor *out, ParticleColor *from, ParticleColor *to, f32 t) __asm__("func_800AB24C");
extern void set_env_color_overlay(void *arg0) __asm__("func_800A9EE0");
extern void set_primary_color_overlay(void *arg0) __asm__("func_800A9DA8");
extern ViewPlayer *get_entity_record(u16 index) __asm__("func_800A6688");
extern u8 *func_800A424C(void *value);
extern void *func_800A42A4(void *value);
extern void append_display_list_call_1(void *displayList) __asm__("func_8007EF1C");
extern void push_cached_perspective_matrix(void *proj, u16 perspNorm) __asm__("func_8007E9C8");
extern void push_cached_matrix_load(void *matrix, u8 params) __asm__("func_8007E824");
extern void func_800786F4(u8 *view, f32 *pos, f32 dx, f32 dz, f32 *out);
extern void func_8010C9E8(PulseEffect *effect, f32 quad[4][3]);

void draw_pulse_effect_shapes(PulseEffect *effect) __asm__("func_8010C450");

void draw_pulse_effect_shapes(PulseEffect *effect)
{
    f32 quad[4][3];
    ParticleColor env;
    ParticleColor prim;
    s32 count;
    s32 i;
    s32 j;
    f32 w;
    f32 h;
    f32 *pos;
    ViewPlayer *player;
    u8 *view;
    u16 perspNorm;
    u8 *proj;
    f32 *v;
    s32 pulse;

    push_overlay_display_list_variant(1);
    load_table_texture(2, effect->texture0, 0);
    load_table_texture(2, effect->texture1, 1);
    func_8007EB04(2);
    count = get_difficulty_level();
    pulse = effect->pulse0;
    lerp_color(&env, &D_80142CB0, &D_80142CB4, ((pulse ^ ((s32)(pulse << 24) >> 31)) & 0x7F) / 127.0f);
    pulse = effect->pulse1;
    lerp_color(&prim, &D_80142CB8, &D_80142CBC, ((pulse ^ ((s32)(pulse << 24) >> 31)) & 0x7F) / 127.0f);
    prim.alpha = effect->alpha;
    set_env_color_overlay(&env);
    set_primary_color_overlay(&prim);
    w = effect->width;
    h = effect->height;
    pos = effect->pos;
    for (i = 0; i < count; i++) {
        player = get_entity_record(i);
        view = func_800A424C(player);
        perspNorm = player->perspNorm;
        proj = player->projection;
        append_display_list_call_1(func_800A42A4(player));
        push_cached_perspective_matrix(proj, perspNorm);
        push_cached_matrix_load(view + 0x48, 1);
        switch (effect->shape) {
        case 2:
            func_800786F4(view, pos, -w, -h, quad[0]);
            func_800786F4(view, pos, w, -h, quad[1]);
            func_800786F4(view, pos, w, h, quad[2]);
            func_800786F4(view, pos, -w, h, quad[3]);
            func_8010C9E8(effect, quad);
            break;
        case 4:
            for (j = 0; j < 4; j++) {
                s32 *idx = D_80142BE0[j];
                v = D_80142B80[idx[0]];
                quad[0][0] = pos[0] + w * v[0];
                quad[0][1] = pos[1] + h * v[1];
                quad[0][2] = pos[2] + w * v[2];
                v = D_80142B80[idx[1]];
                quad[1][0] = pos[0] + w * v[0];
                quad[1][1] = pos[1] + h * v[1];
                quad[1][2] = pos[2] + w * v[2];
                v = D_80142B80[idx[2]];
                quad[2][0] = pos[0] + w * v[0];
                quad[2][1] = pos[1] + h * v[1];
                quad[2][2] = pos[2] + w * v[2];
                v = D_80142B80[idx[3]];
                quad[3][0] = pos[0] + w * v[0];
                quad[3][1] = pos[1] + h * v[1];
                quad[3][2] = pos[2] + w * v[2];
                func_8010C9E8(effect, quad);
            }
            break;
        case 3:
            for (j = 0; j < 3; j++) {
                s32 *idx = D_80142C68[j];
                v = D_80142C20[idx[0]];
                quad[0][0] = pos[0] + w * v[0];
                quad[0][1] = pos[1] + h * v[1];
                quad[0][2] = pos[2] + w * v[2];
                v = D_80142C20[idx[1]];
                quad[1][0] = pos[0] + w * v[0];
                quad[1][1] = pos[1] + h * v[1];
                quad[1][2] = pos[2] + w * v[2];
                v = D_80142C20[idx[2]];
                quad[2][0] = pos[0] + w * v[0];
                quad[2][1] = pos[1] + h * v[1];
                quad[2][2] = pos[2] + w * v[2];
                v = D_80142C20[idx[3]];
                quad[3][0] = pos[0] + w * v[0];
                quad[3][1] = pos[1] + h * v[1];
                quad[3][2] = pos[2] + w * v[2];
                func_8010C9E8(effect, quad);
            }
            break;
        }
    }
}
