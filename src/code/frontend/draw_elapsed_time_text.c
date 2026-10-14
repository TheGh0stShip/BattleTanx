#include "types.h"

extern s32 format_string(char *out, const char *format, ...) __asm__("func_8011CC84");
extern void set_texture_draw_position(s32 x, s32 y) __asm__("func_8010552C");
extern void set_texture_draw_color(s32 red, s32 green, s32 blue, s32 alpha) __asm__("func_8010555C");
extern void draw_text_mark_digits(void **displayList, char *text) __asm__("func_80105750");
extern char D_80073D14[];
extern char D_80073D18[];
extern void *gTextDisplayList __asm__("D_8037A174");

void draw_elapsed_time_text(s32 ticks) __asm__("func_800D1AD0");

void draw_elapsed_time_text(s32 ticks) {
    char secondsText[8];
    char text[0x10];
    s32 seconds;
    s32 minutes;

    seconds = ticks / 30;
    minutes = seconds / 60;
    format_string(secondsText, D_80073D14, seconds % 60 + 100);
    format_string(text, D_80073D18, minutes, secondsText + 1);
    set_texture_draw_color(0xFF, 0xFF, 0xFF, 0xFF);
    set_texture_draw_position(0xEC, 0x5E);
    draw_text_mark_digits(&gTextDisplayList, text);
}
