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

extern u8 D_80327D40;
extern u8 D_80327D41;
extern u8 D_80327D42;
extern u64 D_80327D48;
extern u64 D_80327D50;
extern u64 D_80327D58;
extern u8 D_80327D60;
extern s32 D_80327D64;
extern u8 D_80133C38[];
extern u8 D_80133CAC[];

void draw_sequence_c_captions(Gfx **list) __asm__("func_800C3730");

void draw_sequence_c_captions(Gfx **list) {
    Gfx *gfx = *list;
    u64 now;
    f32 f;

    select_texture_draw_entry(4);
    now = TIME_USEC();
    if (D_80327D42) {
        D_80327D42 = 0;
        D_80327D48 = TIME_USEC() + D_80327D64;
        D_80327D50 = TIME_USEC() + 2000000;
        D_80327D58 = TIME_USEC() + (D_80327D64 - 2000000);
        D_80327D60 = 0;
    }
    if (now < D_80327D48) {
        if (now <= D_80327D50) {
            f = (f32)(D_80327D50 - now) / 2000000.0f;
            f = 1.0f - f;
            D_80327D60 = f * 255.0f;
        }
        if (now >= D_80327D58) {
            f = (f32)(now - D_80327D58) / 2000000.0f;
            f = 1.0f - f;
            D_80327D60 = f * 255.0f;
        }
    }
    if (D_80327D40 == 5) {
        draw_filled_rectangle(&gfx, 0, 0, 34, 240, 0, 0, 0, 255);
        draw_filled_rectangle(&gfx, 0, 0, 320, 19, 0, 0, 0, 255);
        draw_filled_rectangle(&gfx, 0, 134, 320, 134, 0, 0, 0, 255);
        draw_filled_rectangle(&gfx, 286, 0, 34, 240, 0, 0, 0, 255);
        begin_text_draw(&gfx);
        set_texture_draw_position(0, 150);
        set_texture_draw_color(200, 200, 200, D_80327D60);
        switch (D_80327D41) {
        case 0:
            if (now > D_80327D48) {
                D_80327D42 = 1;
                D_80327D41 = 1;
                D_80327D64 = 10000000;
            }
            draw_text_lines_centered(&gfx, D_80133C38, 4, 12, 0, 320);
            break;
        case 1:
            if (now > D_80327D48) {
                D_80327D42 = 1;
                D_80327D41 = 2;
            }
            draw_text_lines_centered(&gfx, D_80133CAC, 4, 12, 0, 320);
            break;
        }
    }
    *list = gfx;
}
