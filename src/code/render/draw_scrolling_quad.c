#include "types.h"

typedef struct QuadVertex {
    f32 x;
    f32 y;
    f32 z;
} QuadVertex;

extern void reset_render_record_halfwords(void) __asm__("func_800A9C20");
extern void flush_vertex_batch_overlay(void) __asm__("func_800A9CC4");
extern void append_vertex_xyz(f32 x, f32 y, f32 z) __asm__("func_800A9FC4");
extern void emit_triangle_overlay(s32 a, s32 b, s32 c) __asm__("func_800AA328");
extern void set_render_frame_scaled_size(f32 scaleX, f32 scaleY) __asm__("func_800AB0A4");
extern f32 D_8007558C;
extern u16 D_80142CC0;

void draw_scrolling_quad(s32 unused, QuadVertex *v) __asm__("func_8010C9E8");

void draw_scrolling_quad(s32 unused, QuadVertex *v) {
    f32 one = D_8007558C;

    D_80142CC0 += 0x64;
    reset_render_record_halfwords();
    set_render_frame_scaled_size(one, one);
    append_vertex_xyz(v->x, v->y, v->z);
    v++;
    set_render_frame_scaled_size(0.0f, one);
    append_vertex_xyz(v->x, v->y, v->z);
    v++;
    set_render_frame_scaled_size(0.0f, 0.0f);
    append_vertex_xyz(v->x, v->y, v->z);
    v++;
    set_render_frame_scaled_size(one, 0.0f);
    append_vertex_xyz(v->x, v->y, v->z);
    flush_vertex_batch_overlay();
    emit_triangle_overlay(0, 1, 2);
    emit_triangle_overlay(0, 2, 3);
}
