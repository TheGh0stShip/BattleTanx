#include "types.h"

extern void set_texture_draw_color(u8 red, u8 green, u8 blue, u8 alpha) __asm__("func_8010555C");
extern void func_80102050(s32, s32, s32, s32);
extern void func_8010316C(void);
extern void set_texture_draw_mode(s32 mode) __asm__("func_801054C0");
extern void func_8010698C(s32 *);
extern void func_801054E0(s32);
extern void func_800DD310(s32, s32, s32, s32, s32, char *);
extern s32 format_string(char *out, const char *format, ...) __asm__("func_8011CC84");
extern void set_texture_draw_position(s32 x, s32 y) __asm__("func_8010552C");
extern void draw_text_in_span(s32 *displayList, char *text, s32 x, s32 width) __asm__("func_80105A50");
extern char D_80073C80[];
extern u8 D_80134E64;
extern s32 D_8037A174;

void draw_formatted_value_label(s32 show, s32 arg1, s32 arg2, s32 arg3, s32 arg4) __asm__("func_800D1410");

void draw_formatted_value_label(s32 show, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    char value[16];
    char text[32];

    set_texture_draw_color(0xFA, 0x1E, 0x1E, 0xFF);
    func_80102050(0x1C, 0x17, 1, 1);
    func_8010316C();
    set_texture_draw_mode(8);
    set_texture_draw_color(0xFF, 0, 0, 0xFF);
    func_8010698C(&D_8037A174);
    set_texture_draw_color(0xFF, 0xFF, 0xFF, 0xFF);
    func_801054E0(4);
    if (show != 0) {
        func_800DD310(arg1, arg2, arg3, arg4, D_80134E64, value);
        format_string(text, D_80073C80, value);
        set_texture_draw_position(0, 0xBE);
        draw_text_in_span(&D_8037A174, text, 0, 0x140);
    }
}
