#include "types.h"

typedef struct Gfx {
    u32 w0;
    u32 w1;
} Gfx;

extern void set_text_scale_mode(s32 mode) __asm__("func_801054E0");
extern void set_texture_draw_position(s32 x, s32 y) __asm__("func_8010552C");
extern void set_texture_draw_color(s32 red, s32 green, s32 blue, s32 alpha) __asm__("func_8010555C");
extern void draw_text(Gfx **gfx, char *text, s32 arg2, s32 width) __asm__("func_80105A50");
extern void begin_text_draw(Gfx **gfx) __asm__("func_8010698C");
extern s32 format_string(char *dst, char *fmt, s32 value) __asm__("func_8011CC84");

extern Gfx *D_8037A174;
extern char D_80073D70[];
extern char D_80073D84[];

void draw_value_text_with_notice(s32 level, s32 value) __asm__("func_800D39A4");

void draw_value_text_with_notice(s32 level, s32 value)
{
    char buffer[64];

    set_texture_draw_color(0xFA, 0x1E, 0x1E, 0xFF);
    begin_text_draw(&D_8037A174);
    set_text_scale_mode(2);
    format_string(buffer, D_80073D70, value);
    set_texture_draw_position(0x49, 0x50);
    draw_text(&D_8037A174, buffer, 0, 0x140);
    set_texture_draw_color(0xFF, 0xFF, 0xFF, 0xFF);
    if (level >= 0x2E) {
        set_texture_draw_position(0x2E, 0x6E);
        draw_text(&D_8037A174, D_80073D84, 0, 0x140);
    }
}
