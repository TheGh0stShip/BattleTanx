#include "types.h"

typedef struct MenuLine {
    s32 kind;
    u8 color[4];
    char *text;
} MenuLine;

extern s32 gScrollingTextOffset __asm__("D_801416F0");
extern MenuLine gPauseMenuLines[48] __asm__("D_80142904");

extern void begin_text_draw(void **gfx) __asm__("func_8010698C");
extern void set_texture_draw_color(s32 red, s32 green, s32 blue, s32 alpha) __asm__("func_8010555C");
extern void set_texture_draw_position(s32 x, s32 y) __asm__("func_8010552C");
extern void select_texture_draw_entry(s32 index) __asm__("func_801054E0");
extern void draw_text(void **gfx, char *text, s32 x, s32 width) __asm__("func_80105A50");

void draw_scrolling_menu_lines(void **gfxp) __asm__("func_80105290");

void draw_scrolling_menu_lines(void **gfxp)
{
    void *gfx;
    s32 i;

    gfx = *gfxp;
    begin_text_draw(&gfx);
    for (i = 0; i < 48; i++) {
        if ((u32)(gScrollingTextOffset + i * 14 + 9) < 0x149) {
            set_texture_draw_color(gPauseMenuLines[i].color[0], gPauseMenuLines[i].color[1],
                                   gPauseMenuLines[i].color[2], gPauseMenuLines[i].color[3]);
            set_texture_draw_position(50, gScrollingTextOffset + i * 14);
            select_texture_draw_entry(gPauseMenuLines[i].kind);
            draw_text(&gfx, gPauseMenuLines[i].text, 0, 320);
        }
    }
    gScrollingTextOffset--;
    *gfxp = gfx;
}
