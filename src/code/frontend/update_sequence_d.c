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
extern void func_80079BB4(s32);
extern void func_80079BF4(s32);
extern void func_800C4090(void);
extern s32 D_80125794;
extern u8 D_80327E50;
extern u64 D_80327E58;
extern s32 D_80327E60;
extern u64 D_80327E68;
extern u64 D_80327E70;
extern u64 D_80327E78;
extern u64 D_80327E80;
extern s32 D_80327E88;
extern u8 D_80327E8C;
extern u8 D_80327E8D;
extern u8 D_80327E8E;
extern u64 D_80327E98;
extern u8 D_80327EB1;
extern u8 D_80327EB2;
extern u8 D_80327EB3;
extern u64 D_80327EB8;
extern u8 D_80133E80[];

void update_sequence_d(void) __asm__("func_800C4254");

void update_sequence_d(void) {
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
    switch (D_80327E50) {
    case 0:
        if (now > D_80327E58 || D_80327EB2) {
            D_80327E50 = 1;
            D_80327E68 = TIME_USEC() + 9000000;
            D_80327E68 = TIME_USEC() + 9000000;
            D_80327E70 = TIME_USEC();
            D_80327E78 = TIME_USEC() + 3000000;
            D_80327E80 = TIME_USEC() + 6000000;
            D_80327E88 = 0;
            D_80327E8E = 0;
            D_80327E8D = 0;
            D_80327E8C = 255;
            func_80079BB4(13);
            func_80079BF4((s16)(D_80125794 << 12));
        } else {
            D_80327EB8 = D_80327E58 - now;
            f = (f32)D_80327EB8 / 12000000.0f;
            D_80327E60 = f * 240.0f;
            begin_text_draw(&gFrontendDisplayList);
            set_texture_draw_color(200, 200, 200, 255);
            set_texture_draw_position(0, D_80327E60);
            draw_text_lines_centered(&gTextDisplayList, D_80133E80, 11, 12, 0, 320);
        }
        break;
    case 1:
        if (now > D_80327E68 || D_80327EB2) {
            D_80327E50 = 4;
            D_80327EB1 = 1;
            D_80327EB3 = 1;
            D_80327E98 = 10000000;
        } else {
            if (now > D_80327E78) {
                D_80327E88 = 1;
                D_80327E8D = 255;
            }
            if (now > D_80327E80) {
                D_80327E88 = 2;
                D_80327E8E = 255;
                func_80079BB4(6);
                func_80079BF4((s16)(D_80125794 << 12));
            }
            func_800C4090();
        }
        break;
    }
}
