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
extern s32 func_800C082C(s32, s32);
extern void func_800BD994(void);
extern void func_800BDEF8(void);
extern void func_800BE45C(void);
extern s32 D_80125794;
extern char D_80073470[];
extern u8 D_80327C30;
extern u8 D_80327C31;
extern u8 D_80327C32;
extern u8 D_80327C33;
extern u8 D_80327C34;
extern u8 D_80327C35;
extern s32 D_80327C54;
extern u8 D_80327C58;
extern u64 D_80327C60;
extern u64 D_80327C70;
extern u64 D_80327C78;
extern s32 D_80327C80;
extern u64 D_80327C88;
extern u64 D_80327C98;
extern u64 D_80327CA0;
extern s32 D_80327CA8;
extern u8 D_80327CAD;
extern u8 D_80327CAE;
extern u8 D_80327CAF;
extern u64 D_80327CB0;
extern u64 D_80327CB8;
extern s32 D_80327CC0;
extern u64 D_80327CC8;
extern u64 D_80327CD0;
extern u64 D_80327CD8;
extern u64 D_80327CE0;
extern s32 D_80327CE8;
extern u8 D_80327CEC;
extern u64 D_80327CF0;
extern u64 D_80327CF8;
extern s32 D_80327D00;
extern u64 D_80327D08;
extern u64 D_80327D10;
extern u64 D_80327D18;
extern u64 D_80327D20;
extern s32 D_80327D28;
extern u8 D_80327D2C;
extern u8 D_80327D2D;
extern u64 D_80327D30;
extern s32 D_80327D38;

void update_sequence_b(void) __asm__("func_800BE99C");

void update_sequence_b(void) {
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
    switch (D_80327C30) {
    case 0:
        if (now > D_80327C60) {
            D_80327C58 = 255;
        } else {
            D_80327D30 = D_80327C60 - now;
            f = (f32)D_80327D30 / 2000000.0f;
            f = 1.0f - f;
            D_80327C58 = f * 255.0f;
        }
        if (now > D_80327C78) {
            D_80327D30 = now - D_80327C78;
            f = (f32)D_80327D30 / 2000000.0f;
            D_80327C80 = f * 255.0f;
        }
        if (now > D_80327C70 || D_80327D2D) {
            D_80327D2C = 1;
            D_80327C30 = 1;
            D_80327C35 = 1;
            D_80327C34 = 0;
            D_80327C54 = 5000000;
            func_80079BD4();
            func_80079BB4(6);
            func_80079BF4((s16)(D_80125794 << 12));
        } else {
            begin_text_draw(&gTextDisplayList);
            set_texture_draw_color(200, 200, 200, D_80327C58);
            set_texture_draw_position(0, 70);
            draw_text_in_span(&gCaptionDisplayList, D_80073470, 0, 320);
            draw_filled_rectangle(&gFrontendDisplayList, 0, 0, 320, 240, 0, 0, 0, D_80327C80);
        }
        break;
    case 2:
        if (now > D_80327C88 || D_80327D2D) {
            D_80327C30 = 3;
            D_80327CC8 = TIME_USEC() + 12000000;
            D_80327CD0 = TIME_USEC();
            D_80327CD8 = TIME_USEC() + 4000000;
            D_80327CE0 = TIME_USEC() + 8000000;
            D_80327CE8 = 0;
            D_80327C33 = 0;
            D_80327C32 = 0;
            D_80327C31 = 255;
            D_80327CF0 = TIME_USEC() + 1000000;
            D_80327CF8 = TIME_USEC() + 10000000;
            D_80327CEC = 0;
            D_80327D00 = 0;
        } else {
            if (now > D_80327C98) {
                D_80327CA8 = 1;
                D_80327CAD = 255;
            }
            if (now > D_80327CA0) {
                D_80327CA8 = 2;
                D_80327CAE = 255;
            }
            if (now > D_80327CB0) {
                D_80327CAF = 0;
            } else {
                D_80327D30 = D_80327CB0 - now;
                f = (f32)D_80327D30 / 1000000.0f;
                D_80327CAF = f * 255.0f;
            }
            if (now > D_80327CB8) {
                D_80327D30 = now - D_80327CB8;
                f = (f32)D_80327D30 / 5000000.0f;
                D_80327CC0 = f * 255.0f;
            }
            func_800BD994();
        }
        break;
    case 3:
        if (now > D_80327CC8 || D_80327D2D) {
            D_80327C30 = 4;
            D_80327D08 = TIME_USEC() + 15000000;
            D_80327D10 = TIME_USEC() + 5000000;
            D_80327D18 = TIME_USEC() + 5000000;
            D_80327D20 = TIME_USEC() + 5000000;
            D_80327D28 = 0;
            func_80079BD4();
            func_80079BB4(0);
            func_80079BF4((s16)(D_80125794 << 12));
            if (D_80327D38 != -1) {
                func_800798C0(D_80327D38);
                D_80327D38 = -1;
            }
        } else {
            if (now > D_80327CD8) {
                if (!D_80327C32) {
                    D_80327D38 = func_800C082C(42, 0x7000);
                }
                D_80327CE8 = 1;
                D_80327C32 = 255;
            }
            if (now > D_80327CE0) {
                D_80327CE8 = 2;
                D_80327C33 = 255;
            }
            if (now > D_80327CF0) {
                D_80327CEC = 0;
            } else {
                D_80327D30 = D_80327CF0 - now;
                f = (f32)D_80327D30 / 1000000.0f;
                D_80327CEC = f * 255.0f;
            }
            if (now > D_80327CF8) {
                D_80327D30 = now - D_80327CF8;
                f = (f32)D_80327D30 / 2000000.0f;
                D_80327D00 = f * 255.0f;
            }
            func_800BDEF8();
        }
        break;
    case 4:
        if (now > D_80327D08 || D_80327D2D) {
            D_80327D2C = 1;
        } else {
            if (now > D_80327D18) {
                D_80327D28 = 1;
            }
            if (now > D_80327D20) {
                D_80327D28 = 2;
            }
            func_800BE45C();
        }
        break;
    }
}
