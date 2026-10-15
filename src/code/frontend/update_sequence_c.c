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
extern s32 func_800C3EA4(s32, s32);
extern void func_800C0EDC(void);
extern void func_800C10D8(void);
extern void func_800C12D4(void);
extern void func_800C17D0(void);
extern void func_800C1B54(void);
extern void func_800C2050(void);
extern s32 D_80125794;
extern char D_80073500[];
extern u8 D_80327D40;
extern u8 D_80327D41;
extern u8 D_80327D42;
extern s32 D_80327D64;
extern u8 D_80327D68;
extern u64 D_80327D70;
extern u64 D_80327D80;
extern u64 D_80327D88;
extern s32 D_80327D90;
extern u64 D_80327D98;
extern u64 D_80327DA0;
extern u64 D_80327DA8;
extern u64 D_80327DB0;
extern u64 D_80327DB8;
extern u64 D_80327DC0;
extern s32 D_80327DC8;
extern u8 D_80327DCC;
extern u8 D_80327DCD;
extern u8 D_80327DCE;
extern u64 D_80327DD0;
extern u64 D_80327DD8;
extern u64 D_80327DE0;
extern u8 D_80327DE8;
extern u8 D_80327DE9;
extern u8 D_80327DEA;
extern u8 D_80327DEB;
extern u64 D_80327E00;
extern u64 D_80327E08;
extern s32 D_80327E10;
extern u8 D_80327E15;
extern u8 D_80327E16;
extern u64 D_80327DF0;
extern u64 D_80327E20;
extern u64 D_80327E28;
extern u8 D_80327E30;
extern u8 D_80327E31;
extern u64 D_80327E38;
extern s32 D_80327E40;

void update_sequence_c(void) __asm__("func_800C224C");

void update_sequence_c(void) {
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
    switch (D_80327D40) {
    case 0:
        if (now > D_80327D70) {
            D_80327D68 = 255;
        } else {
            D_80327E38 = D_80327D70 - now;
            f = (f32)D_80327E38 / 2000000.0f;
            f = 1.0f - f;
            D_80327D68 = f * 255.0f;
        }
        if (now > D_80327D88) {
            D_80327E38 = now - D_80327D88;
            f = (f32)D_80327E38 / 2000000.0f;
            D_80327D90 = f * 255.0f;
        }
        if (now > D_80327D80 || D_80327E31) {
            D_80327D40 = 1;
            D_80327D98 = TIME_USEC() + 7000000;
            func_80079BD4();
            func_80079BB4(7);
            func_80079BF4((s16)(D_80125794 << 12));
        } else {
            begin_text_draw(&gTextDisplayList);
            set_texture_draw_color(200, 200, 200, D_80327D68);
            set_texture_draw_position(0, 70);
            draw_text_in_span(&gCaptionDisplayList, D_80073500, 0, 320);
            draw_filled_rectangle(&gFrontendDisplayList, 0, 0, 320, 240, 0, 0, 0, D_80327D90);
        }
        break;
    case 1:
        if (now > D_80327D98 || D_80327E31) {
            D_80327DA0 = TIME_USEC() + 6000000;
            D_80327D40 = 2;
        } else {
            func_800C0EDC();
        }
        break;
    case 2:
        if (now > D_80327DA0 || D_80327E31) {
            D_80327DC8 = 0;
            D_80327DA8 = TIME_USEC() + 9000000;
            D_80327DB0 = TIME_USEC();
            D_80327DB8 = TIME_USEC() + 3000000;
            D_80327DC0 = TIME_USEC() + 6000000;
            D_80327DCE = 0;
            D_80327DCD = 0;
            D_80327DCC = 255;
            D_80327D40 = 3;
        } else {
            func_800C10D8();
        }
        break;
    case 3:
        if (now > D_80327DA8 || D_80327E31) {
            D_80327D40 = 4;
            D_80327DD0 = TIME_USEC() + 8000000;
            D_80327DD8 = TIME_USEC() + 2000000;
            D_80327DE0 = TIME_USEC() + 6000000;
            D_80327DE9 = 0;
            D_80327DE8 = 255;
            D_80327DEB = 1;
            D_80327DEA = 1;
        } else {
            if (now > D_80327DB8) {
                D_80327DC8 = 1;
                D_80327DCD = 255;
            }
            if (now > D_80327DC0) {
                D_80327DC8 = 2;
                D_80327DCE = 255;
            }
            func_800C12D4();
        }
        break;
    case 4:
        if (now > D_80327DD0 || D_80327E31) {
            D_80327E30 = 1;
            D_80327D40 = 5;
            D_80327D42 = 1;
            D_80327D41 = 0;
            D_80327D64 = 10000000;
            func_80079BD4();
            func_80079BB4(8);
            func_80079BF4((s16)(D_80125794 << 12));
            if (D_80327E40 != -1) {
                func_800798C0(D_80327E40);
                D_80327E40 = -1;
            }
        } else {
            if (now >= D_80327DD8 && now <= D_80327DE0) {
                if (D_80327DEA) {
                    D_80327DEA = 0;
                    func_800C3EA4(42, 0x7000);
                }
                D_80327E38 = D_80327DE0 - now;
                f = (f32)D_80327E38 / 4000000.0f;
                f = 1.0f - f;
                D_80327DE9 = f * 255.0f;
            }
            func_800C17D0();
        }
        break;
    case 6:
        if (now > D_80327DF0 || D_80327E31) {
            D_80327D40 = 7;
            D_80327E20 = TIME_USEC() + 6000000;
        } else {
            if (now > D_80327E00) {
                D_80327E10 = 1;
                D_80327E15 = 255;
            }
            if (now > D_80327E08) {
                D_80327E10 = 2;
                D_80327E16 = 255;
            }
            func_800C1B54();
        }
        break;
    case 7:
        if (now > D_80327E20 || D_80327E31) {
            D_80327E30 = 1;
            D_80327E28 = TIME_USEC() + 6000000;
            D_80327D40 = 8;
            if (D_80327E40 != -1) {
                func_800798C0(D_80327E40);
                D_80327E40 = -1;
            }
        } else {
            func_800C2050();
        }
        break;
    }
}
