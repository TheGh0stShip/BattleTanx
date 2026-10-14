#include "types.h"

typedef struct Gfx {
    u32 w0;
    u32 w1;
} Gfx;

extern void func_80102050(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
extern void func_8010316C(void);
extern void func_800DD310(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, char *out);
extern void set_text_scale_mode(s32 mode) __asm__("func_801054E0");
extern void set_texture_draw_position(s32 x, s32 y) __asm__("func_8010552C");
extern void set_texture_draw_color(s32 red, s32 green, s32 blue, s32 alpha) __asm__("func_8010555C");
extern void draw_text(Gfx **gfx, char *text, s32 arg2, s32 width) __asm__("func_80105A50");
extern void begin_text_draw(Gfx **gfx) __asm__("func_8010698C");
extern s32 format_string(char *dst, char *fmt, ...) __asm__("func_8011CC84");

extern Gfx *D_8037A174;
extern u8 D_80134E64;
extern char D_80073C80[];
extern char D_80073D90[];

void draw_formatted_value_notice(s32 arg0, s32 arg1, s32 arg2, s32 arg3) __asm__("func_800D3B2C");

void draw_formatted_value_notice(s32 arg0, s32 arg1, s32 arg2, s32 arg3)
{
    char title[32];
    char value[16];
    char line[32];

    set_texture_draw_color(0xFA, 0x1E, 0x1E, 0xFF);
    func_80102050(0x1C, 0x17, 0, 1);
    func_8010316C();
    set_texture_draw_color(0xFF, 0, 0, 0xFF);
    begin_text_draw(&D_8037A174);
    set_text_scale_mode(2);
    format_string(title, D_80073D90);
    set_texture_draw_position(0x49, 0x1E);
    draw_text(&D_8037A174, title, 0, 0x140);
    set_texture_draw_color(0xFF, 0xFF, 0xFF, 0xFF);
    set_text_scale_mode(4);
    func_800DD310(arg0, arg1, arg2, arg3, D_80134E64, value);
    format_string(line, D_80073C80, value);
    set_texture_draw_position(0, 0xBE);
    draw_text(&D_8037A174, line, 0, 0x140);
}
