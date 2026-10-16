#include "types.h"

typedef struct Vec3f {
    f32 x;
    f32 y;
    f32 z;
} Vec3f;

typedef struct ViewMatrix {
    f32 m[4][4];
    f32 extra;
} ViewMatrix;

extern s32 D_8035BCC0;
extern s8 D_8035BC74[2];
extern u16 D_8035BC76;
extern u16 D_8035BC78;
extern u8 D_8035BC70;
extern u8 D_8035BC71;
extern u8 D_8035BC73;
extern f32 D_8035BC68;
extern f32 D_8035BC6C;
extern u8 D_8035BC80[];
extern u16 D_8035BCC4;
extern u32 D_80141050;
extern u8 D_80141058[];
extern u8 D_801410B8[];
extern u8 D_80141120[3];
extern u8 D_80141124[];
extern u8 D_80141128[];
extern u8 D_8014112C[];
extern u8 D_80141130[];

extern void func_800A7650(ViewMatrix *m);
extern void func_80113460(ViewMatrix *m, f32 eyeX, f32 eyeY, f32 eyeZ, f32 atX, f32 atY, f32 atZ, f32 upX, f32 upY,
                          f32 upZ);
extern void func_800AB24C(s32 *out, void *a, void *b, f32 t);
extern void func_800A9F48(s32 *a);
extern void func_800A9EE0(s32 *a);
extern void func_800A9DA8(u8 *color);
extern void func_8007EF1C(void *a);
extern void func_800AA518(s32 a, u16 b);
extern void func_8007EB04(s32 a);
extern void func_800AACCC(s32 a, s32 b, s32 c);
extern void *get_entity_record(u16 index) __asm__("func_800A6688");
extern void func_800A424C(void *owner);
extern void func_8007E9C8(void *a, u16 b);
extern void func_8007E824(ViewMatrix *m, s32 b);
extern f32 angle_sin(u16 angle) __asm__("func_800F3AE0");
extern f32 angle_cos(u16 angle) __asm__("func_800F3B40");
extern void reset_render_record_halfwords(void) __asm__("func_800A9C20");
extern void flush_vertex_batch_overlay(void) __asm__("func_800A9CC4");
extern void append_vertex_xyz(f32 x, f32 y, f32 z) __asm__("func_800A9FC4");
extern void emit_triangle_overlay(s32 a, s32 b, s32 c) __asm__("func_800AA328");
extern void set_render_frame_scaled_size(f32 scaleX, f32 scaleY) __asm__("func_800AB0A4");

void func_800F4794(s32 arg0);

static inline void build_quad(Vec3f *v, f32 *pos, u16 angle)
{
    f32 s;
    f32 c;
    f32 w;
    f32 h;

    s = angle_cos(angle);
    c = angle_sin(angle);
    w = D_8035BC68;
    h = D_8035BC6C;
    v[0].z = v[3].z = pos[2] + w * -c;
    v[0].y = v[1].y = pos[1] - h;
    v[2].y = v[3].y = pos[1] + h;
    v[0].x = v[3].x = pos[0] + w * s;
    v[1].z = v[2].z = pos[2] - w * -c;
    v[1].x = v[2].x = pos[0] - w * s;
}


void func_800F4794(s32 arg0)
{
    Vec3f v[4];
    f32 pos[3];
    s32 tintA[2];
    s32 tintB[2];
    ViewMatrix m = { { { 1.0f, 0.0f, 0.0f, 0.0f },
                       { 0.0f, 1.0f, 0.0f, 0.0f },
                       { 0.0f, 0.0f, 1.0f, 0.0f },
                       { 0.0f, 0.0f, 0.0f, 1.0f } },
                     0.0f };
    f32 dx;
    f32 dz;
    f32 s;
    f32 c;
    f32 e;
    f32 d;
    f32 w;
    f32 h;
    s32 i;
    s32 k;

    D_8035BCC0 = 0;
    func_800A7650(&m);
    func_80113460(&m, 375.0f, 65.0f, -1500.0f, 375.0f, 65.0f, -1300.0f, 0.0f, 1.0f, 0.0f);
    D_8035BC74[0] += 1;
    D_8035BC74[1] += 1;
    D_8035BC76 += D_8035BC78;
    if (D_8035BC76 >= 0x100) {
        D_8035BC76 = 0;
        D_8035BC70++;
        D_8035BC71++;
        D_8035BC70 = D_8035BC70 % D_80141050;
        D_8035BC71 = D_8035BC71 % D_80141050;
    }
    k = D_8035BC74[0] ^ (D_8035BC74[0] >> 7);
    func_800AB24C(tintA, D_80141124, D_80141128, (f32)(k & 0x7F) / 127.0f);
    k = (D_8035BC74[1] ^ (D_8035BC74[1] >> 7)) & 0x7F;
    func_800AB24C(tintB, D_8014112C, D_80141130, (f32)k / 127.0f);
    func_800A9F48(tintB);
    func_800A9EE0(tintA);
    D_80141120[0] = D_80141120[1] = D_80141120[2] = D_8035BC73;
    func_800A9DA8(D_80141120);
    func_8007EF1C(D_801410B8);
    func_800AA518(3, arg0);
    func_8007EB04(2);
    s = angle_cos(0);
    c = angle_sin(0);
    dz = s * 4.0f;
    dx = c * 4.0f;
    for (i = 0; i < 2; i++) {
        pos[0] = dx * i + 375.0f;
        pos[1] = 50.0f;
        pos[2] = dz * i + -1400.0f;
        build_quad(v, pos, 0);
        func_800A424C(get_entity_record(0));
        func_8007E9C8(D_8035BC80, D_8035BCC4);
        func_8007E824(&m, 1);
        reset_render_record_halfwords();
        set_render_frame_scaled_size(0.0f, 1.0f);
        append_vertex_xyz(v[0].x, v[0].y, v[0].z);
        set_render_frame_scaled_size(1.0f, 1.0f);
        append_vertex_xyz(v[1].x, v[1].y, v[1].z);
        set_render_frame_scaled_size(1.0f, 0.0f);
        append_vertex_xyz(v[2].x, v[2].y, v[2].z);
        set_render_frame_scaled_size(0.0f, 0.0f);
        append_vertex_xyz(v[3].x, v[3].y, v[3].z);
        flush_vertex_batch_overlay();
        emit_triangle_overlay(0, 1, 2);
        emit_triangle_overlay(0, 2, 3);
    }
    func_8007EF1C(D_80141058);
    func_800AACCC(0, D_8035BC70, 1);
    for (i = 0; i < 2; i++) {
        pos[0] = dx * i + 375.0f;
        pos[1] = 50.0f;
        pos[2] = dz * i + -1400.0f;
        build_quad(v, pos, 0);
        func_800A424C(get_entity_record(0));
        func_8007E9C8(D_8035BC80, D_8035BCC4);
        func_8007E824(&m, 1);
        reset_render_record_halfwords();
        set_render_frame_scaled_size(0.0f, 1.0f);
        append_vertex_xyz(v[0].x, v[0].y, v[0].z);
        set_render_frame_scaled_size(1.0f, 1.0f);
        append_vertex_xyz(v[1].x, v[1].y, v[1].z);
        set_render_frame_scaled_size(1.0f, 0.0f);
        append_vertex_xyz(v[2].x, v[2].y, v[2].z);
        set_render_frame_scaled_size(0.0f, 0.0f);
        append_vertex_xyz(v[3].x, v[3].y, v[3].z);
        flush_vertex_batch_overlay();
        emit_triangle_overlay(0, 1, 2);
        emit_triangle_overlay(0, 2, 3);
    }
}
