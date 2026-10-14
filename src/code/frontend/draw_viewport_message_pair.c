#include "types.h"

typedef struct Gfx {
    u32 w0;
    u32 w1;
} Gfx;

extern void set_text_scale_mode(s32 mode) __asm__("func_801054E0");
extern void set_texture_draw_position(s32 x, s32 y) __asm__("func_8010552C");
extern void set_texture_draw_color(s32 red, s32 green, s32 blue, s32 alpha) __asm__("func_8010555C");
extern void draw_text(Gfx **gfx, char *text, s32 x, s32 width) __asm__("func_80105A50");
extern void begin_text_draw(Gfx **gfx) __asm__("func_8010698C");

extern Gfx *D_8037A174;
extern char *D_80126154[];
extern char *D_801261EC[];

void draw_viewport_message_pair(s32 messageId, s32 viewport, s32 viewportCount, char *customText)
    __asm__("func_80101E9C");

void draw_viewport_message_pair(s32 messageId, s32 viewport, s32 viewportCount, char *customText)
{
    s32 x = 0xF;
    s32 width = 0x131;
    s32 y = 0x78;

    switch (viewportCount) {
    case 0:
        break;
    case 1:
        y = 0xB4;
        if (viewport == 0) {
            y = 0x3C;
        }
        break;
    case 2:
        switch (viewport) {
        case 0:
            y = 0x3C;
            break;
        case 1:
            y = 0xAA;
            width = 0xA0;
            break;
        case 2:
            y = 0xAA;
            x = 0xA0;
            break;
        }
        break;
    case 3:
        y = 0xAA;
        if ((u32) viewport < 2) {
            y = 0x3C;
        }
        if (viewport == 0 || viewport == 2) {
            width = 0xA0;
        } else {
            x = 0xA0;
        }
        break;
    }
    begin_text_draw(&D_8037A174);
    set_text_scale_mode(4);
    set_texture_draw_position(0, y);
    set_texture_draw_color(0xFF, 0xFF, 0xFF, 0xB4);
    if (messageId == 0x27) {
        draw_text(&D_8037A174, customText + 0x220, x, width);
        set_texture_draw_position(0, y + 0xA);
        draw_text(&D_8037A174, customText + 0x240, x, width);
    } else {
        draw_text(&D_8037A174, D_80126154[messageId], x, width);
        set_texture_draw_position(0, y + 0xA);
        draw_text(&D_8037A174, D_801261EC[messageId], x, width);
    }
}
