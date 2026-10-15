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
extern void draw_text_lines(void *context, u8 *text, s32 lineCount, s32 lineHeight, s32 maxChars) __asm__("func_80105C68");
extern void func_800798C0(s32);
extern s32 func_800B9C0C(u8 *);
extern s32 func_800B9C34(s32, s32);
extern u64 D_803277A0;
extern s32 D_803277D0;
extern s32 D_803277D4;
extern s32 D_803277D8;
extern s32 D_803277DC;
extern u64 D_803278C0;
extern s32 D_803278C8;
extern s32 D_803278CC;
extern s32 D_803278D0;
extern s32 D_803278D4;
extern s32 D_803278D8;
extern u64 D_80327A30;
extern u64 D_80327A38;
extern u64 D_80327A40;
extern u64 D_80327A48;
extern s32 D_80327A50;
extern u8 D_80327A54;
extern u8 D_80327B22;
extern u8 D_80327B23;
extern u8 D_80327B24;
extern u64 D_80327B28;
extern s32 D_80327B30;
extern s32 D_80327B34;
extern u8 D_80327B44;
extern u8 D_803276E0;
extern u8 D_801324CC[];
extern u8 D_8013250C[];
extern u8 D_8013259C[];
extern u8 D_801327EC[];
extern u8 D_8013281C[];
extern u8 D_8013285C[];
extern u8 D_801328D8[];
extern u8 D_8013297C[];
extern u8 D_80132AC8[];
extern u8 D_80132B04[];
extern u8 D_80132BB0[];
extern u8 D_80132C30[];

void draw_opening_captions(Gfx **list) __asm__("func_800B8804");

void draw_opening_captions(Gfx **list) {
    Gfx *gfx;
    u64 now;
    u64 t;
    f32 f;
    s32 n;

    if (D_80327B44) {
        if (D_80327B34 != -1) {
            func_800798C0(D_80327B34);
            D_80327B34 = -1;
        }
    }
    gfx = *list;
    select_texture_draw_entry(4);
    switch (D_803276E0) {
    case 4:
    draw_filled_rectangle(&gfx, 0, 0, 34, 240, 0, 0, 0, 255);
    draw_filled_rectangle(&gfx, 0, 0, 320, 19, 0, 0, 0, 255);
    draw_filled_rectangle(&gfx, 0, 134, 320, 134, 0, 0, 0, 255);
    draw_filled_rectangle(&gfx, 286, 0, 34, 240, 0, 0, 0, 255);
        if (D_80327B22) {
            D_803277A0 = TIME_USEC();
            D_803277D0 = func_800B9C0C(D_801324CC);
            D_803277D4 = func_800B9C0C(D_8013250C);
            D_803277D8 = func_800B9C0C(D_8013259C);
            D_80327B22 = 0;
            D_80327B34 = func_800B9C34(36, 0x7000);
        }
        D_80327B28 = TIME_USEC() - D_803277A0;
        D_80327B30 = (f32)D_80327B28 / 66666.0f;
        begin_text_draw(&gfx);
        set_texture_draw_color(200, 200, 200, 255);
        set_texture_draw_position(34, 150);
        switch (D_803277DC) {
        case 0:
            n = D_803277D0;
            if (D_80327B30 < n) {
                n = D_80327B30;
            }
            D_80327B30 = n;
            if (D_80327B30 == D_803277D0) {
                D_803277DC = 1;
                D_80327B22 = 1;
                func_800798C0(D_80327B34);
                D_80327B34 = -1;
            }
            D_80327B30 = (D_80327B30 > 0) ? D_80327B30 : 1;
            draw_text_lines(&gfx, D_801324CC, 2, 12, D_80327B30);
            break;
        case 1:
            n = D_803277D4;
            if (D_80327B30 < n) {
                n = D_80327B30;
            }
            D_80327B30 = n;
            if (D_80327B30 == D_803277D4) {
                D_803277DC = 2;
                D_80327B22 = 1;
                func_800798C0(D_80327B34);
                D_80327B34 = -1;
            }
            D_80327B30 = (D_80327B30 > 0) ? D_80327B30 : 1;
            draw_text_lines(&gfx, D_8013250C, 5, 12, D_80327B30);
            break;
        case 2:
            n = D_803277D8;
            if (D_80327B30 < n) {
                n = D_80327B30;
            }
            D_80327B30 = n;
            if (n <= 0) {
                n = 1;
            }
            D_80327B30 = n;
            if (D_80327B30 == D_803277D8) {
                func_800798C0(D_80327B34);
                D_80327B34 = -1;
            }
            draw_text_lines(&gfx, D_8013259C, 5, 12, D_80327B30);
            break;
        }
        break;
    case 9:
    draw_filled_rectangle(&gfx, 0, 0, 34, 240, 0, 0, 0, 255);
    draw_filled_rectangle(&gfx, 0, 0, 320, 19, 0, 0, 0, 255);
    draw_filled_rectangle(&gfx, 0, 134, 320, 134, 0, 0, 0, 255);
    draw_filled_rectangle(&gfx, 286, 0, 34, 240, 0, 0, 0, 255);
        if (D_80327B23) {
            D_803278C0 = TIME_USEC();
            D_803278C8 = func_800B9C0C(D_80132AC8);
            D_803278CC = func_800B9C0C(D_80132B04);
            D_803278D0 = func_800B9C0C(D_80132BB0);
            D_803278D4 = func_800B9C0C(D_80132C30);
            D_80327B23 = 0;
            D_80327B34 = func_800B9C34(36, 0x7000);
        }
        D_80327B28 = TIME_USEC() - D_803278C0;
        D_80327B30 = (f32)D_80327B28 / 66666.0f;
        begin_text_draw(&gfx);
        set_texture_draw_position(34, 150);
        switch (D_803278D8) {
        case 0:
            n = D_803278C8;
            if (D_80327B30 < n) {
                n = D_80327B30;
            }
            D_80327B30 = n;
            if (D_80327B30 == D_803278C8) {
                D_803278D8 = 1;
                D_80327B23 = 1;
                func_800798C0(D_80327B34);
                D_80327B34 = -1;
            }
            D_80327B30 = (D_80327B30 > 0) ? D_80327B30 : 1;
            draw_text_lines(&gfx, D_80132AC8, 2, 12, D_80327B30);
            break;
        case 1:
            n = D_803278CC;
            if (D_80327B30 < n) {
                n = D_80327B30;
            }
            D_80327B30 = n;
            if (D_80327B30 == D_803278CC) {
                D_803278D8 = 2;
                D_80327B23 = 1;
                func_800798C0(D_80327B34);
                D_80327B34 = -1;
            }
            D_80327B30 = (D_80327B30 > 0) ? D_80327B30 : 1;
            draw_text_lines(&gfx, D_80132B04, 5, 12, D_80327B30);
            break;
        case 2:
            n = D_803278D0;
            if (D_80327B30 < n) {
                n = D_80327B30;
            }
            D_80327B30 = n;
            if (D_80327B30 == D_803278D0) {
                D_803278D8 = 3;
                D_80327B23 = 1;
                func_800798C0(D_80327B34);
                D_80327B34 = -1;
            }
            D_80327B30 = (D_80327B30 > 0) ? D_80327B30 : 1;
            draw_text_lines(&gfx, D_80132BB0, 4, 12, D_80327B30);
            break;
        case 3:
            n = D_803278D4;
            if (D_80327B30 < n) {
                n = D_80327B30;
            }
            D_80327B30 = n;
            if (n <= 0) {
                n = 1;
            }
            D_80327B30 = n;
            if (D_80327B30 == D_803278D4) {
                func_800798C0(D_80327B34);
                D_80327B34 = -1;
            }
            draw_text_lines(&gfx, D_80132C30, 4, 12, D_80327B30);
            break;
        }
        break;
    case 14:
    draw_filled_rectangle(&gfx, 0, 0, 34, 240, 0, 0, 0, 255);
    draw_filled_rectangle(&gfx, 0, 0, 320, 19, 0, 0, 0, 255);
    draw_filled_rectangle(&gfx, 0, 134, 320, 134, 0, 0, 0, 255);
    draw_filled_rectangle(&gfx, 286, 0, 34, 240, 0, 0, 0, 255);
        now = TIME_USEC();
        if (D_80327B24) {
            D_80327A30 = TIME_USEC() + D_80327A38;
            D_80327A40 = TIME_USEC() + 2000000;
            t = TIME_USEC() - 2000000;
            D_80327A48 = t + D_80327A38;
            D_80327B24 = 0;
            D_80327A54 = 0;
        }
        now = TIME_USEC();
        begin_text_draw(&gfx);
        set_texture_draw_position(34, 150);
        if (now < D_80327A30) {
            if (now <= D_80327A40) {
                D_80327B28 = D_80327A40 - now;
                f = (f32)D_80327B28 / 2000000.0f;
                f = 1.0f - f;
                D_80327A54 = f * 255.0f;
            }
            if (now >= D_80327A48) {
                D_80327B28 = now - D_80327A48;
                f = (f32)D_80327B28 / 2000000.0f;
                f = 1.0f - f;
                D_80327A54 = f * 255.0f;
            }
        }
        set_texture_draw_color(200, 200, 200, D_80327A54);
        switch (D_80327A50) {
        case 0:
            if (now > D_80327A30) {
                D_80327A50 = 1;
                D_80327B24 = 1;
                D_80327A38 = 6000000;
            }
            draw_text_lines_centered(&gfx, D_801327EC, 2, 12, 0, 320);
            break;
        case 1:
            if (now > D_80327A30) {
                D_80327A50 = 2;
                D_80327B24 = 1;
                D_80327A38 = 7000000;
            }
            draw_text_lines_centered(&gfx, D_8013281C, 2, 12, 0, 320);
            break;
        case 2:
            if (now > D_80327A30) {
                D_80327A50 = 3;
                D_80327B24 = 1;
                D_80327A38 = 10000000;
            }
            draw_text_lines_centered(&gfx, D_8013285C, 4, 12, 0, 320);
            break;
        case 3:
            if (now > D_80327A30) {
                D_80327A50 = 4;
                D_80327B24 = 1;
                D_80327A38 = 7000000;
            }
            draw_text_lines_centered(&gfx, D_801328D8, 5, 12, 0, 320);
            break;
        case 4:
            if (now > D_80327A30) {
                D_80327A50 = 5;
            }
            draw_text_lines_centered(&gfx, D_8013297C, 1, 12, 0, 320);
            break;
        }
        break;
    }
    *list = gfx;
}
