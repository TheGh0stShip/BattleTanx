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

#define GFX_COMMAND(packet, first, second) { \
    Gfx *command = (packet); \
    command->w0 = (first); \
    command->w1 = (second); \
}

extern Gfx *gFrontendDisplayList __asm__("D_803276D4");
extern Gfx *gTextDisplayList __asm__("D_803276D4");
extern Gfx *gCaptionDisplayList __asm__("D_803276D4");
extern void draw_text_in_span(Gfx **gfx, char *text, s32 left, s32 right) __asm__("func_80105A50");
extern void func_800798C0(s32);
extern void func_80079BB4(s32);
extern void func_80079BD4(void);
extern void func_80079BF4(s32);
extern s32 func_800BD19C(s32, s32);
extern void func_800BA764(void);
extern void func_800BA960(void);
extern void func_800BAB5C(void);
extern void func_800BAD58(void);
extern void func_800BB254(void);
extern void func_800BB450(void);
extern s32 D_80125794;
extern char D_80073400[];
extern u8 D_80327B50;
extern u8 D_80327B51;
extern u64 D_80327B58;
extern u64 D_80327B68;
extern u64 D_80327B70;
extern s32 D_80327B78;
extern u64 D_80327B80;
extern u64 D_80327B88;
extern u64 D_80327B90;
extern u64 D_80327B98;
extern u64 D_80327BA0;
extern u64 D_80327BA8;
extern u64 D_80327BB0;
extern s32 D_80327BB8;
extern u8 D_80327BBC;
extern u8 D_80327BBD;
extern u8 D_80327BBE;
extern u64 D_80327BC0;
extern s32 D_80327BE4;
extern u64 D_80327BE8;
extern u64 D_80327BF0;
extern u8 D_80327C0C;
extern u8 D_80327C0F;
extern u8 D_80327C10;
extern u8 D_80327C11;
extern u8 D_80327C12;
extern u64 D_80327C18;
extern s32 D_80327C20;

void update_sequence_a(void) __asm__("func_800BB69C");

void update_sequence_a(void) {
    u64 now;
    f32 f;

    draw_filled_rectangle(&gFrontendDisplayList, 0, 0, 320, 240, 0, 0, 0, 255);
    GFX_COMMAND(gFrontendDisplayList++, 0xE7000000U, 0);
    GFX_COMMAND(gFrontendDisplayList++, 0xBA001402U, 0);
    GFX_COMMAND(gFrontendDisplayList++, 0xFCFFFFFFU, 0xFFFCF279U);
    GFX_COMMAND(gFrontendDisplayList++, 0xB900031DU, 0x0F0A4000);
    GFX_COMMAND(gFrontendDisplayList++, 0xBA001301U, 0);
    GFX_COMMAND(gFrontendDisplayList++, 0xBA001001U, 0);
    GFX_COMMAND(gFrontendDisplayList++, 0xBA000C02U, 0);
    GFX_COMMAND(gFrontendDisplayList++, 0xBA000903U, 0xC00);
    GFX_COMMAND(gFrontendDisplayList++, 0xBA000E02U, 0x8000);
    GFX_COMMAND(gFrontendDisplayList++, 0xFA000101U, 0xFFFFFFFFU);
    now = TIME_USEC();
    select_texture_draw_entry(3);
    switch (D_80327B50) {
    case 255:
        if (now > D_80327B58) {
            D_80327B51 = 255;
        } else {
            D_80327C18 = D_80327B58 - now;
            f = (f32)D_80327C18 / 2000000.0f;
            f = 1.0f - f;
            D_80327B51 = f * 255.0f;
        }
        if (now > D_80327B70) {
            D_80327C18 = now - D_80327B70;
            f = (f32)D_80327C18 / 2000000.0f;
            D_80327B78 = f * 255.0f;
        }
        if (now > D_80327B68 || D_80327C10) {
            D_80327C12 = 1;
            D_80327C0F = 1;
            D_80327B50 = 0;
            D_80327C11 = 0;
            D_80327BE4 = 5000000;
            func_80079BD4();
            func_80079BB4(10);
            func_80079BF4((s16)(D_80125794 << 12));
        } else {
            begin_text_draw(&gTextDisplayList);
            set_texture_draw_color(200, 200, 200, D_80327B51);
            set_texture_draw_position(0, 70);
            draw_text_in_span(&gCaptionDisplayList, D_80073400, 0, 320);
            draw_filled_rectangle(&gFrontendDisplayList, 0, 0, 320, 240, 0, 0, 0, D_80327B78);
        }
        break;
    case 1:
        if (now > D_80327B80 || D_80327C10) {
            D_80327B50 = 2;
            D_80327B88 = TIME_USEC() + 5000000;
        } else {
            func_800BA764();
        }
        break;
    case 2:
        if (now > D_80327B88 || D_80327C10) {
            D_80327B50 = 3;
            D_80327B90 = TIME_USEC() + 5000000;
        } else {
            func_800BA960();
        }
        break;
    case 3:
        if (now > D_80327B90 || D_80327C10) {
            D_80327B50 = 4;
            D_80327C12 = 1;
            D_80327C0F = 1;
            D_80327C11 = 0;
            D_80327BE4 = 4000000;
        } else {
            func_800BAB5C();
        }
        break;
    case 5:
        if (now > D_80327B98 || D_80327C10) {
            D_80327B50 = 6;
            D_80327C0F = 1;
            D_80327C12 = 1;
            D_80327C11 = 0;
            D_80327BE4 = 7000000;
            func_80079BD4();
            func_80079BB4(10);
            func_80079BF4((s16)(D_80125794 << 12));
            if (D_80327C20 != -1) {
                func_800798C0(D_80327C20);
                D_80327C20 = -1;
            }
        } else {
            if (now > D_80327BA0) {
                if (!D_80327BBC) {
                    D_80327C20 = func_800BD19C(40, 0x7000);
                }
                D_80327BBC = 255;
            }
            if (now > D_80327BA8) {
                D_80327BB8 = 1;
                D_80327BBD = 255;
            }
            if (now > D_80327BB0) {
                D_80327BB8 = 2;
                D_80327BBE = 255;
            }
            func_800BAD58();
        }
        break;
    case 7:
        if (now > D_80327BC0 || D_80327C10) {
            D_80327B50 = 8;
            D_80327C0F = 1;
            D_80327C12 = 1;
            D_80327C11 = 0;
            D_80327BE4 = 5000000;
        } else {
            func_800BB254();
        }
        break;
    case 9:
        if (now > D_80327BE8 || D_80327C10) {
            D_80327C0F = 1;
        } else {
            if (now > D_80327BF0) {
                D_80327C0C = 255;
            }
            func_800BB450();
        }
        break;
    }
}
