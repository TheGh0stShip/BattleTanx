#include "types.h"

extern void *gTextDisplayList __asm__("D_8037A174");

extern void set_texture_draw_color(s32 red, s32 green, s32 blue, s32 alpha) __asm__("func_8010555C");
extern void set_texture_draw_position(s32 x, s32 y) __asm__("func_8010552C");
extern void draw_text_integer(void **displayList, s64 value) __asm__("func_80105688");

void draw_white_value_10C_46(s32 value) __asm__("func_800D1998");

void draw_white_value_10C_46(s32 value) {
    set_texture_draw_color(0xFF, 0xFF, 0xFF, 0xFF);
    set_texture_draw_position(0x10C, 0x46);
    draw_text_integer(&gTextDisplayList, value);
}
