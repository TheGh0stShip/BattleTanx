#include "types.h"

extern s32 D_8037A174;
extern char D_80073D9C[];

extern s32 format_string(char *out, const char *format, ...) __asm__("func_8011CC84");
extern void set_texture_draw_position(s32 x, s32 y) __asm__("func_8010552C");
extern void draw_text_in_span(s32 *displayList, char *text, s32 x, s32 width) __asm__("func_80105A50");

void draw_centered_formatted_label(s32 value) __asm__("func_800D3C84");

void draw_centered_formatted_label(s32 value)
{
    char text[32];

    format_string(text, D_80073D9C, value);
    set_texture_draw_position(0, 0x3E);
    draw_text_in_span(&D_8037A174, text, 0, 0x140);
}
