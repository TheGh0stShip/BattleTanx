#include "types.h"

typedef struct Gfx {
    u32 w0;
    u32 w1;
} Gfx;

extern u64 osClockRate __asm__("D_80145DA0");
extern u64 osGetTime(void) __asm__("func_801120A0");
extern void draw_filled_rectangle(Gfx **list, s32 x, s32 y, s32 width, s32 height, s32 red, s32 green,
                                  s32 blue, s32 alpha) __asm__("func_800F4DFC");
extern void select_texture_draw_entry(s32 index) __asm__("func_801054E0");
extern void begin_text_draw(Gfx **gfx) __asm__("func_8010698C");
extern void set_texture_draw_position(s32 x, s32 y) __asm__("func_8010552C");
extern void set_texture_draw_color(s32 red, s32 green, s32 blue, s32 alpha) __asm__("func_8010555C");
extern void draw_text_lines_centered(void *context, u8 *text, s32 lineCount, s32 lineHeight, s32 left,
                                     s32 right) __asm__("func_80105D90");


#define TIME_USEC() (osGetTime() * 1000000 / osClockRate)

extern u8 D_80327C12;
extern u64 D_80327BC8;
extern u64 D_80327BD0;
extern u64 D_80327BD8;
extern u8 D_80327BE0;
extern s32 D_80327BE4;

extern u8 D_80327B50;
extern u8 D_80327C11;
extern u8 D_80132F00[];
extern u8 D_80132F4C[];
extern u8 D_80132F80[];
extern u8 D_801330C4[];
extern u8 D_801330E4[];
extern u8 D_80133100[];
extern u8 D_80133220[];
extern u8 D_801332FC[];
extern u8 D_80133360[];

void draw_sequence_a_captions(Gfx **list) __asm__("func_800BC4A8");

void draw_sequence_a_captions(Gfx **list) {
    Gfx *gfx = *list;
    u64 now;
    f32 f;

    select_texture_draw_entry(4);
    now = TIME_USEC();
    if (D_80327C12) {
        D_80327C12 = 0;
        D_80327BC8 = TIME_USEC() + D_80327BE4;
        D_80327BD0 = TIME_USEC() + 2000000;
        D_80327BD8 = TIME_USEC() + (D_80327BE4 - 2000000);
        D_80327BE0 = 0;
    }
    if (now < D_80327BC8) {
        if (now <= D_80327BD0) {
            f = (f32)(D_80327BD0 - now) / 2000000.0f;
            f = 1.0f - f;
            D_80327BE0 = f * 255.0f;
        }
        if (now >= D_80327BD8) {
            f = (f32)(now - D_80327BD8) / 2000000.0f;
            f = 1.0f - f;
            D_80327BE0 = f * 255.0f;
        }
    }
    switch (D_80327B50) {
    case 0:
        draw_filled_rectangle(&gfx, 0, 0, 34, 240, 0, 0, 0, 255);
        draw_filled_rectangle(&gfx, 0, 0, 320, 19, 0, 0, 0, 255);
        draw_filled_rectangle(&gfx, 0, 134, 320, 134, 0, 0, 0, 255);
        draw_filled_rectangle(&gfx, 286, 0, 34, 240, 0, 0, 0, 255);
        begin_text_draw(&gfx);
        set_texture_draw_position(0, 150);
        set_texture_draw_color(200, 200, 200, D_80327BE0);
        switch (D_80327C11) {
        case 0:
            if (now > D_80327BC8) {
                D_80327C12 = 1;
                D_80327C11 = 1;
                D_80327BE4 = 5000000;
            }
            draw_text_lines_centered(&gfx, D_80132F00, 3, 12, 0, 320);
            break;
        case 1:
            if (now > D_80327BC8) {
                D_80327C12 = 1;
                D_80327C11 = 2;
                D_80327BE4 = 5000000;
            }
            draw_text_lines_centered(&gfx, D_80132F4C, 2, 12, 0, 320);
            break;
        case 2:
            if (now > D_80327BC8) {
                D_80327C11 = 3;
            }
            draw_text_lines_centered(&gfx, D_80132F80, 3, 12, 0, 320);
            break;
        }
        break;
    case 4:
        draw_filled_rectangle(&gfx, 0, 0, 34, 240, 0, 0, 0, 255);
        draw_filled_rectangle(&gfx, 0, 0, 320, 19, 0, 0, 0, 255);
        draw_filled_rectangle(&gfx, 0, 134, 320, 134, 0, 0, 0, 255);
        draw_filled_rectangle(&gfx, 286, 0, 34, 240, 0, 0, 0, 255);
        begin_text_draw(&gfx);
        set_texture_draw_position(0, 150);
        set_texture_draw_color(200, 200, 200, D_80327BE0);
        switch (D_80327C11) {
        case 0:
            if (now > D_80327BC8) {
                D_80327C12 = 1;
                D_80327C11 = 1;
                D_80327BE4 = 4000000;
            }
            draw_text_lines_centered(&gfx, D_801330C4, 1, 12, 0, 320);
            break;
        case 1:
            if (now > D_80327BC8) {
                D_80327C12 = 1;
                D_80327C11 = 2;
                D_80327BE4 = 5000000;
            }
            draw_text_lines_centered(&gfx, D_801330E4, 1, 12, 0, 320);
            break;
        case 2:
            if (now > D_80327BC8) {
                D_80327C11 = 3;
            }
            draw_text_lines_centered(&gfx, D_80133100, 2, 12, 0, 320);
            break;
        }
        break;
    case 6:
        draw_filled_rectangle(&gfx, 0, 0, 34, 240, 0, 0, 0, 255);
        draw_filled_rectangle(&gfx, 0, 0, 320, 19, 0, 0, 0, 255);
        draw_filled_rectangle(&gfx, 0, 134, 320, 134, 0, 0, 0, 255);
        draw_filled_rectangle(&gfx, 286, 0, 34, 240, 0, 0, 0, 255);
        begin_text_draw(&gfx);
        set_texture_draw_position(0, 150);
        set_texture_draw_color(200, 200, 200, D_80327BE0);
        draw_text_lines_centered(&gfx, D_80133220, 4, 12, 0, 320);
        break;
    case 8:
        draw_filled_rectangle(&gfx, 0, 0, 34, 240, 0, 0, 0, 255);
        draw_filled_rectangle(&gfx, 0, 0, 320, 19, 0, 0, 0, 255);
        draw_filled_rectangle(&gfx, 0, 134, 320, 134, 0, 0, 0, 255);
        draw_filled_rectangle(&gfx, 286, 0, 34, 240, 0, 0, 0, 255);
        begin_text_draw(&gfx);
        begin_text_draw(&gfx);
        set_texture_draw_position(0, 150);
        set_texture_draw_color(200, 200, 200, D_80327BE0);
        switch (D_80327C11) {
        case 0:
            if (now > D_80327BC8) {
                D_80327C12 = 1;
                D_80327C11 = 1;
                D_80327BE4 = 5000000;
            }
            draw_text_lines_centered(&gfx, D_801332FC, 3, 12, 0, 320);
            break;
        case 1:
            if (now > D_80327BC8) {
                D_80327C12 = 1;
                D_80327C11 = 2;
            }
            draw_text_lines_centered(&gfx, D_80133360, 2, 12, 0, 320);
            break;
        }
        break;
    }
    *list = gfx;
}
