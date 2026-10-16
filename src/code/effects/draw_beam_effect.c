#include "types.h"

typedef struct ParticleColor {
    u8 red;
    u8 green;
    u8 blue;
    u8 alpha;
} ParticleColor;

typedef struct BeamEffect {
    u8 pad00[0x18];
    u16 angle;
    u8 pad1A[0xE];
    f32 halfWidth;
    f32 halfHeight;
    u8 texture;
    u8 pad31[2];
    u8 shade;
    u8 pulse0;
    u8 pulse1;
} BeamEffect;

typedef struct ViewPlayer {
    u8 pad000[0xFC];
    u16 perspNorm;
    u8 pad0FE[2];
    u8 projection[0x40];
} ViewPlayer;

extern ParticleColor D_80142CD4;
extern ParticleColor D_80142CD8;
extern ParticleColor D_80142CDC;
extern ParticleColor D_80142CE0;
extern ParticleColor D_80142CE4;

extern s32 get_difficulty_level(void) __asm__("func_8007AAA0");
extern void push_overlay_display_list_variant(u16 variant) __asm__("func_800AA3D0");
extern void load_table_texture(u32 table, u16 index, s32 tile) __asm__("func_800AACCC");
extern void func_8007EB04(s32 mode);
extern void func_800AA518(s32 a, s32 b);
extern void lerp_color(ParticleColor *out, ParticleColor *from, ParticleColor *to, f32 t) __asm__("func_800AB24C");
extern void set_env_color_overlay(void *arg0) __asm__("func_800A9EE0");
extern void set_primary_color_overlay(void *arg0) __asm__("func_800A9DA8");
extern void func_800A9F48(void *arg0);
extern ViewPlayer *get_entity_record(u16 index) __asm__("func_800A6688");
extern u8 *func_800A424C(void *value);
extern void *func_800A42A4(void *value);
extern void append_display_list_call_1(void *displayList) __asm__("func_8007EF1C");
extern void push_cached_perspective_matrix(void *proj, u16 perspNorm) __asm__("func_8007E9C8");
extern void push_cached_matrix_load(void *matrix, u8 params) __asm__("func_8007E824");
extern f32 func_800F3AE0(u16 angle);
extern f32 func_800F3B40(u16 angle);
extern void func_800A9C20(void);
extern void func_800A9CC4(void);
extern void func_800AB0A4(f32 s, f32 t);
extern void func_800A9FC4(f32 x, f32 y, f32 z);
extern void func_800AA328(s32 a, s32 b, s32 c);

void draw_beam_effect(BeamEffect *effect, f32 *origin) __asm__("func_8010CE24");

void draw_beam_effect(BeamEffect *effect, f32 *origin)
{
    f32 quad[4][3];
    ParticleColor env;
    ParticleColor prim;
    f32 base[3];
    s32 count;
    s32 i;
    s32 k;
    f32 stepX;
    f32 stepZ;
    ViewPlayer *player;
    u8 *view;
    u16 perspNorm;
    u8 *proj;
    s32 pulse;

    pulse = effect->pulse0;
    lerp_color(&env, &D_80142CD8, &D_80142CDC, ((pulse ^ ((s32)(pulse << 24) >> 31)) & 0x7F) / 127.0f);
    pulse = effect->pulse1;
    lerp_color(&prim, &D_80142CE0, &D_80142CE4, ((pulse ^ ((s32)(pulse << 24) >> 31)) & 0x7F) / 127.0f);
    func_800A9F48(&prim);
    set_env_color_overlay(&env);
    D_80142CD4.red = D_80142CD4.green = D_80142CD4.blue = effect->shade;
    set_primary_color_overlay(&D_80142CD4);
    push_overlay_display_list_variant(4);
    func_800AA518(1, 0);
    func_8007EB04(2);
    perspNorm = 0;
    count = get_difficulty_level();
    {
        f32 s = func_800F3B40(effect->angle);
        f32 c = func_800F3AE0(effect->angle);

        stepZ = s * 4.0f;
        stepX = c * 4.0f;
    }
    proj = 0;
    for (k = 0; k < 2; k++) {
        base[0] = origin[0] + stepX * k;
        base[2] = origin[2] + stepZ * k;
        base[1] = origin[1];
        {
        u16 angle = effect->angle;
        f32 s;
        f32 c;
        f32 dx;
        f32 dz;
        f32 x0;
        f32 x1;
        f32 y0;
        f32 y1;
        f32 z0;
        f32 z1;
        f32 h;

        s = func_800F3B40(angle);
        c = func_800F3AE0(angle);
        h = effect->halfHeight;
        dz = effect->halfWidth * -c;
        z0 = base[2] + dz;
        y0 = base[1] - h;
        z1 = base[2] - dz;
        dx = effect->halfWidth * s;
        x0 = base[0] + dx;
        y1 = base[1] + h;
        x1 = base[0] - dx;
        quad[0][1] = quad[1][1] = y0;
        quad[2][1] = quad[3][1] = y1;
        quad[0][2] = quad[3][2] = z0;
        quad[0][0] = quad[3][0] = x0;
        quad[1][2] = quad[2][2] = z1;
        quad[1][0] = quad[2][0] = x1;
        }
        for (i = 0; i < count; i++) {
            player = get_entity_record(i);
            view = func_800A424C(player);
            proj = player->projection;
            perspNorm = player->perspNorm;
            append_display_list_call_1(func_800A42A4(player));
            push_cached_perspective_matrix(proj, perspNorm);
            push_cached_matrix_load(view + 0x48, 1);
            func_800A9C20();
            func_800AB0A4(0.0f, 1.0f);
            func_800A9FC4(quad[0][0], quad[0][1], quad[0][2]);
            func_800AB0A4(1.0f, 1.0f);
            func_800A9FC4(quad[1][0], quad[1][1], quad[1][2]);
            func_800AB0A4(1.0f, 0.0f);
            func_800A9FC4(quad[2][0], quad[2][1], quad[2][2]);
            func_800AB0A4(0.0f, 0.0f);
            func_800A9FC4(quad[3][0], quad[3][1], quad[3][2]);
            func_800A9CC4();
            func_800AA328(0, 1, 2);
            func_800AA328(0, 2, 3);
        }
    }
    push_overlay_display_list_variant(3);
    load_table_texture(0, effect->texture, 1);
    for (k = 0; k < 2; k++) {
        base[0] = origin[0] + stepX * k;
        base[2] = origin[2] + stepZ * k;
        base[1] = origin[1];
        {
        u16 angle = effect->angle;
        f32 s;
        f32 c;
        f32 dx;
        f32 dz;
        f32 x0;
        f32 x1;
        f32 y0;
        f32 y1;
        f32 z0;
        f32 z1;
        f32 h;

        s = func_800F3B40(angle);
        c = func_800F3AE0(angle);
        h = effect->halfHeight;
        dz = effect->halfWidth * -c;
        z0 = base[2] + dz;
        y0 = base[1] - h;
        z1 = base[2] - dz;
        dx = effect->halfWidth * s;
        x0 = base[0] + dx;
        y1 = base[1] + h;
        x1 = base[0] - dx;
        quad[0][1] = quad[1][1] = y0;
        quad[2][1] = quad[3][1] = y1;
        quad[0][2] = quad[3][2] = z0;
        quad[0][0] = quad[3][0] = x0;
        quad[1][2] = quad[2][2] = z1;
        quad[1][0] = quad[2][0] = x1;
        }
        for (i = 0; i < count; i++) {
            player = get_entity_record(i);
            view = func_800A424C(player);
            append_display_list_call_1(func_800A42A4(player));
            push_cached_perspective_matrix(proj, perspNorm);
            push_cached_matrix_load(view + 0x48, 1);
            func_800A9C20();
            func_800AB0A4(0.0f, 1.0f);
            func_800A9FC4(quad[0][0], quad[0][1], quad[0][2]);
            func_800AB0A4(1.0f, 1.0f);
            func_800A9FC4(quad[1][0], quad[1][1], quad[1][2]);
            func_800AB0A4(1.0f, 0.0f);
            func_800A9FC4(quad[2][0], quad[2][1], quad[2][2]);
            func_800AB0A4(0.0f, 0.0f);
            func_800A9FC4(quad[3][0], quad[3][1], quad[3][2]);
            func_800A9CC4();
            func_800AA328(0, 1, 2);
            func_800AA328(0, 2, 3);
        }
    }
}
