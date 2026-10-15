#include "types.h"

typedef struct Gfx {
    u32 w0;
    u32 w1;
} Gfx;

typedef struct ResourceBundle {
    s32 count;
    s32 entryOffset[1];
} ResourceBundle;

#define GFX_COMMAND(packet, first, second) { \
    Gfx *command = (packet); \
    command->w0 = (first); \
    command->w1 = (second); \
}

#define BUNDLE_ENTRY(index) (((ResourceBundle *)gResourceTarget)->entryOffset[index] + gResourceTarget)

#define LOAD_BUNDLE_PALETTE(index) \
    GFX_COMMAND(gFrontendDisplayList++, 0xFD100000U, BUNDLE_ENTRY(index)); \
    GFX_COMMAND(gFrontendDisplayList++, 0xE8000000U, 0); \
    GFX_COMMAND(gFrontendDisplayList++, 0xF5000100U, 0x07000000); \
    GFX_COMMAND(gFrontendDisplayList++, 0xE6000000U, 0); \
    GFX_COMMAND(gFrontendDisplayList++, 0xF0000000U, 0x073FC000); \
    GFX_COMMAND(gFrontendDisplayList++, 0xE7000000U, 0)

extern Gfx *gFrontendDisplayList __asm__("D_803276D4");
extern s32 gResourceTarget __asm__("D_803275F4");
extern s32 D_80327614;
extern s32 D_80328410;
extern u8 D_801352CC[][2];
extern char *D_801354EC[];
extern s32 D_8013555C[];
extern s32 D_80135570[];
extern u8 D_801355E4[][2];
extern s32 D_801355F4[];
extern s32 D_8013566C;

extern void draw_filled_rectangle(Gfx **list, s32 left, s32 top, s32 right, s32 bottom, s32 red, s32 green, s32 blue,
                                  s32 alpha) __asm__("func_800F4DFC");
extern s32 select_audio_mode(u32 mode) __asm__("func_800AB95C");
extern void draw_paletted_image(Gfx **list, u8 *texels, s32 arg2, s32 arg3, s32 width, s32 height, s32 tileWidth,
                                s32 tileHeight, s32 x, s32 y, s32 width2, s32 height2, s32 s, s32 t,
                                f32 scaleX, f32 scaleY) __asm__("func_800F3D40");
extern void begin_text_draw(Gfx **gfx) __asm__("func_8010698C");
extern void set_texture_draw_color(s32 red, s32 green, s32 blue, s32 alpha) __asm__("func_8010555C");
extern void select_texture_draw_entry(s32 index) __asm__("func_801054E0");
extern void set_texture_draw_position(s32 x, s32 y) __asm__("func_8010552C");
extern void draw_text(Gfx **gfx, char *text) __asm__("func_80105584");
extern void draw_text_in_span(Gfx **gfx, char *text, s32 left, s32 right) __asm__("func_80105A50");

void draw_territory_select_screen(void) __asm__("func_800D9134");

void draw_territory_select_screen(void)
{
    s32 col;
    s32 i;
    s32 group;
    s32 mode;

    GFX_COMMAND(gFrontendDisplayList++, 0xE7000000U, 0);
    GFX_COMMAND(gFrontendDisplayList++, 0xBA001402U, 0);
    GFX_COMMAND(gFrontendDisplayList++, 0xFCFFFFFFU, 0xFFFCF279U);
    GFX_COMMAND(gFrontendDisplayList++, 0xB900031DU, 0x0F0A4000);
    GFX_COMMAND(gFrontendDisplayList++, 0xBA001301U, 0);
    GFX_COMMAND(gFrontendDisplayList++, 0xBA001001U, 0);
    GFX_COMMAND(gFrontendDisplayList++, 0xBA000C02U, 0);
    GFX_COMMAND(gFrontendDisplayList++, 0xBA000903U, 0xC00);
    GFX_COMMAND(gFrontendDisplayList++, 0xBA000E02U, 0x8000);
    GFX_COMMAND(gFrontendDisplayList++, 0xFCFFFFFFU, 0xFFFCF279U);
    GFX_COMMAND(gFrontendDisplayList++, 0xBA000E02U, 0x8000);
    GFX_COMMAND(gFrontendDisplayList++, 0xFA000101U, 0xFFFFFFFFU);
    LOAD_BUNDLE_PALETTE(11);
    for (i = 0; i < 4; i++) {
        for (col = 0; col < 6; col++) {
            draw_paletted_image(&gFrontendDisplayList, (u8 *)(BUNDLE_ENTRY(11) + 0x200), 2, 1, 0x40, 0x40, 0x20,
                                0x20, col * 64, i * 64, 0x40, 0x40, 0, 0, 1.0f, 1.0f);
        }
    }
    GFX_COMMAND(gFrontendDisplayList++, 0xFD100000U, BUNDLE_ENTRY(3));
    GFX_COMMAND(gFrontendDisplayList++, 0xE8000000U, 0);
    GFX_COMMAND(gFrontendDisplayList++, 0xF5000100U, 0x07000000);
    GFX_COMMAND(gFrontendDisplayList++, 0xE6000000U, 0);
    GFX_COMMAND(gFrontendDisplayList++, 0xF0000000U, 0x073FC000);
    GFX_COMMAND(gFrontendDisplayList++, 0xE7000000U, 0);
    draw_paletted_image(&gFrontendDisplayList, (u8 *)(BUNDLE_ENTRY(3) + 0x200), 2, 1, 0x114, 8, 0x20, 0x20, 0x16, 0xE, 0x114, 8, 0, 0, 1.0f, 1.0f);
    GFX_COMMAND(gFrontendDisplayList++, 0xFD100000U, BUNDLE_ENTRY(0));
    GFX_COMMAND(gFrontendDisplayList++, 0xE8000000U, 0);
    GFX_COMMAND(gFrontendDisplayList++, 0xF5000100U, 0x07000000);
    GFX_COMMAND(gFrontendDisplayList++, 0xE6000000U, 0);
    GFX_COMMAND(gFrontendDisplayList++, 0xF0000000U, 0x073FC000);
    GFX_COMMAND(gFrontendDisplayList++, 0xE7000000U, 0);
    draw_paletted_image(&gFrontendDisplayList, (u8 *)(BUNDLE_ENTRY(0) + 0x200), 2, 1, 0x114, 8, 0x20, 0x20, 0x16, 0x39, 0x114, 8, 0, 0, 1.0f, 1.0f);
    GFX_COMMAND(gFrontendDisplayList++, 0xFD100000U, BUNDLE_ENTRY(0));
    GFX_COMMAND(gFrontendDisplayList++, 0xE8000000U, 0);
    GFX_COMMAND(gFrontendDisplayList++, 0xF5000100U, 0x07000000);
    GFX_COMMAND(gFrontendDisplayList++, 0xE6000000U, 0);
    GFX_COMMAND(gFrontendDisplayList++, 0xF0000000U, 0x073FC000);
    GFX_COMMAND(gFrontendDisplayList++, 0xE7000000U, 0);
    draw_paletted_image(&gFrontendDisplayList, (u8 *)(BUNDLE_ENTRY(0) + 0x200), 2, 1, 0x114, 8, 0x20, 0x20, 0x16, 0xD9, 0x114, 8, 0, 0, 1.0f, 1.0f);
    GFX_COMMAND(gFrontendDisplayList++, 0xFD100000U, BUNDLE_ENTRY(1));
    GFX_COMMAND(gFrontendDisplayList++, 0xE8000000U, 0);
    GFX_COMMAND(gFrontendDisplayList++, 0xF5000100U, 0x07000000);
    GFX_COMMAND(gFrontendDisplayList++, 0xE6000000U, 0);
    GFX_COMMAND(gFrontendDisplayList++, 0xF0000000U, 0x073FC000);
    GFX_COMMAND(gFrontendDisplayList++, 0xE7000000U, 0);
    draw_paletted_image(&gFrontendDisplayList, (u8 *)(BUNDLE_ENTRY(1) + 0x200), 2, 1, 8, 0xC3, 0x20, 0x20, 0x16, 0x16, 8, 0xC3, 0, 0, 1.0f, 1.0f);
    GFX_COMMAND(gFrontendDisplayList++, 0xFD100000U, BUNDLE_ENTRY(2));
    GFX_COMMAND(gFrontendDisplayList++, 0xE8000000U, 0);
    GFX_COMMAND(gFrontendDisplayList++, 0xF5000100U, 0x07000000);
    GFX_COMMAND(gFrontendDisplayList++, 0xE6000000U, 0);
    GFX_COMMAND(gFrontendDisplayList++, 0xF0000000U, 0x073FC000);
    GFX_COMMAND(gFrontendDisplayList++, 0xE7000000U, 0);
    draw_paletted_image(&gFrontendDisplayList, (u8 *)(BUNDLE_ENTRY(2) + 0x200), 2, 1, 8, 0xC3, 0x20, 0x20, 0x122, 0x16, 8, 0xC3, 0, 0, 1.0f, 1.0f);
    GFX_COMMAND(gFrontendDisplayList++, 0xB900031DU, 0x00504240);
    GFX_COMMAND(gFrontendDisplayList++, 0xFD100000U, BUNDLE_ENTRY(13));
    GFX_COMMAND(gFrontendDisplayList++, 0xE8000000U, 0);
    GFX_COMMAND(gFrontendDisplayList++, 0xF5000100U, 0x07000000);
    GFX_COMMAND(gFrontendDisplayList++, 0xE6000000U, 0);
    GFX_COMMAND(gFrontendDisplayList++, 0xF0000000U, 0x073FC000);
    GFX_COMMAND(gFrontendDisplayList++, 0xE7000000U, 0);
    draw_paletted_image(&gFrontendDisplayList, (u8 *)(BUNDLE_ENTRY(13) + 0x200), 2, 1, 0xD1, 0x7F, 0x20, 0x20, 0x2A, 0x4E, 0xD1, 0x7F, 0, 0, 1.0f, 1.0f);
    GFX_COMMAND(gFrontendDisplayList++, 0xFD100000U, BUNDLE_ENTRY(12));
    GFX_COMMAND(gFrontendDisplayList++, 0xE8000000U, 0);
    GFX_COMMAND(gFrontendDisplayList++, 0xF5000100U, 0x07000000);
    GFX_COMMAND(gFrontendDisplayList++, 0xE6000000U, 0);
    GFX_COMMAND(gFrontendDisplayList++, 0xF0000000U, 0x073FC000);
    GFX_COMMAND(gFrontendDisplayList++, 0xE7000000U, 0);
    draw_paletted_image(&gFrontendDisplayList, (u8 *)(BUNDLE_ENTRY(12) + 0x200), 2, 1, 0x100, 0x19, 0x20, 0x20, 0x1F, 0x19, 0x100, 0x19, 0, 0, 1.0f, 1.0f);
    GFX_COMMAND(gFrontendDisplayList++, 0xFC119623U, 0xFF2FFFFFU);
    group = D_80135570[D_8013566C];
    if (group != -1) {
        GFX_COMMAND(gFrontendDisplayList++, 0xFA000101U, 0xFFFFFFFFU);
        GFX_COMMAND(gFrontendDisplayList++, 0xFD100000U,
                    ((s32 *)gResourceTarget)[D_8013555C[group]] + gResourceTarget);
        GFX_COMMAND(gFrontendDisplayList++, 0xE8000000U, 0);
        GFX_COMMAND(gFrontendDisplayList++, 0xF5000100U, 0x07000000);
        GFX_COMMAND(gFrontendDisplayList++, 0xE6000000U, 0);
        GFX_COMMAND(gFrontendDisplayList++, 0xF0000000U, 0x073FC000);
        GFX_COMMAND(gFrontendDisplayList++, 0xE7000000U, 0);
        draw_paletted_image(&gFrontendDisplayList,
                            (u8 *)(((s32 *)gResourceTarget)[D_8013555C[group]] + gResourceTarget + 0x200), 2, 1,
                            0x40, 0x40, 0x20, 0x20, 0xDF, 0x95, 0x40, 0x40, 0, 0, 1.0f, 1.0f);
        LOAD_BUNDLE_PALETTE(10);
        for (i = 0; i < D_80328410; i++) {
            if (D_80135570[i] == group) {
                if (i == D_8013566C) {
                    GFX_COMMAND(gFrontendDisplayList++, 0xFA000101U, 0xC8C8C8FFU);
                } else {
                    GFX_COMMAND(gFrontendDisplayList++, 0xFA000101U, 0x505050FF);
                }
                draw_paletted_image(&gFrontendDisplayList, (u8 *)(BUNDLE_ENTRY(10) + 0x200), 2, 1, 6, 6, 0x20, 0x20,
                                    D_801355E4[i][0] + 0xDF, D_801355E4[i][1] + 0x95, 6, 6, 0, 0, 1.0f, 1.0f);
            }
        }
    }
    begin_text_draw(&gFrontendDisplayList);
    set_texture_draw_color(255, 0xAA, 0, 255);
    select_texture_draw_entry(3);
    set_texture_draw_position(0xDF, 0x87);
    switch (D_801355F4[D_8013566C]) {
    case 0:
        draw_text_in_span(&gFrontendDisplayList, "Easy", 0xDF, 0x11F);
        break;
    case 1:
        draw_text_in_span(&gFrontendDisplayList, "Medium", 0xDF, 0x11F);
        break;
    case 2:
        draw_text_in_span(&gFrontendDisplayList, "Hard", 0xDF, 0x11F);
        break;
    }
    select_texture_draw_entry(3);
    set_texture_draw_position(0x22, 0x42);
    draw_text(&gFrontendDisplayList, D_801354EC[D_8013566C]);
    GFX_COMMAND(gFrontendDisplayList++, 0xFCFFFFFFU, 0xFFFCF279U);
    GFX_COMMAND(gFrontendDisplayList++, 0xBA000E02U, 0x8000);
    GFX_COMMAND(gFrontendDisplayList++, 0xFC119623U, 0xFF2FFFFFU);
    LOAD_BUNDLE_PALETTE(9);
    for (i = 0; i < D_80328410; i++) {
        if (i == D_8013566C) {
            GFX_COMMAND(gFrontendDisplayList++, 0xFA000101U, 0xC8C8C8FFU);
        } else {
            GFX_COMMAND(gFrontendDisplayList++, 0xFA000101U, 0x505050FF);
        }
        draw_paletted_image(&gFrontendDisplayList, (u8 *)(BUNDLE_ENTRY(9) + 0x200), 2, 1, 8, 7, 0x20, 0x20,
                            D_801352CC[i][0], D_801352CC[i][1], 8, 7, 0, 0, 1.0f, 1.0f);
    }
    begin_text_draw(&gFrontendDisplayList);
    set_texture_draw_color(200, 200, 200, 255);
    select_texture_draw_entry(3);
    set_texture_draw_position(0x31, 0xCE);
    draw_text(&gFrontendDisplayList, "HELP");
    mode = select_audio_mode(0);
    if (D_80327614 != 0) {
        draw_filled_rectangle(&gFrontendDisplayList, 0x3E, 0x4C, 0xC3, 0x55, 0, 0, 0, 0xC8);
        GFX_COMMAND(gFrontendDisplayList++, 0xFCFFFFFFU, 0xFFFCF279U);
        GFX_COMMAND(gFrontendDisplayList++, 0xBA000E02U, 0x8000);
        GFX_COMMAND(gFrontendDisplayList++, 0xB900031DU, 0x00504240);
        GFX_COMMAND(gFrontendDisplayList++, 0xFD100000U, BUNDLE_ENTRY(6));
        GFX_COMMAND(gFrontendDisplayList++, 0xE8000000U, 0);
        GFX_COMMAND(gFrontendDisplayList++, 0xF5000100U, 0x07000000);
        GFX_COMMAND(gFrontendDisplayList++, 0xE6000000U, 0);
        GFX_COMMAND(gFrontendDisplayList++, 0xF0000000U, 0x073FC000);
        GFX_COMMAND(gFrontendDisplayList++, 0xE7000000U, 0);
        draw_paletted_image(&gFrontendDisplayList, (u8 *)(BUNDLE_ENTRY(6) + 0x200), 2, 1, 9, 9, 0x20, 0x20, 0x47, 0x56, 9, 9, 0, 0, 1.0f, 1.0f);
        GFX_COMMAND(gFrontendDisplayList++, 0xFD100000U, BUNDLE_ENTRY(8));
        GFX_COMMAND(gFrontendDisplayList++, 0xE8000000U, 0);
        GFX_COMMAND(gFrontendDisplayList++, 0xF5000100U, 0x07000000);
        GFX_COMMAND(gFrontendDisplayList++, 0xE6000000U, 0);
        GFX_COMMAND(gFrontendDisplayList++, 0xF0000000U, 0x073FC000);
        GFX_COMMAND(gFrontendDisplayList++, 0xE7000000U, 0);
        draw_paletted_image(&gFrontendDisplayList, (u8 *)(BUNDLE_ENTRY(8) + 0x200), 2, 1, 9, 9, 0x20, 0x20, 0x54, 0x56, 9, 9, 0, 0, 1.0f, 1.0f);
        GFX_COMMAND(gFrontendDisplayList++, 0xFD100000U, BUNDLE_ENTRY(0));
        GFX_COMMAND(gFrontendDisplayList++, 0xE8000000U, 0);
        GFX_COMMAND(gFrontendDisplayList++, 0xF5000100U, 0x07000000);
        GFX_COMMAND(gFrontendDisplayList++, 0xE6000000U, 0);
        GFX_COMMAND(gFrontendDisplayList++, 0xF0000000U, 0x073FC000);
        GFX_COMMAND(gFrontendDisplayList++, 0xE7000000U, 0);
        draw_paletted_image(&gFrontendDisplayList, (u8 *)(BUNDLE_ENTRY(0) + 0x200), 2, 1, 9, 9, 0x20, 0x20, 0x54, 0x65, 9, 9, 0, 0, 1.0f, 1.0f);
        GFX_COMMAND(gFrontendDisplayList++, 0xFD100000U, BUNDLE_ENTRY(10));
        GFX_COMMAND(gFrontendDisplayList++, 0xE8000000U, 0);
        GFX_COMMAND(gFrontendDisplayList++, 0xF5000100U, 0x07000000);
        GFX_COMMAND(gFrontendDisplayList++, 0xE6000000U, 0);
        GFX_COMMAND(gFrontendDisplayList++, 0xF0000000U, 0x073FC000);
        GFX_COMMAND(gFrontendDisplayList++, 0xE7000000U, 0);
        draw_paletted_image(&gFrontendDisplayList, (u8 *)(BUNDLE_ENTRY(10) + 0x200), 2, 1, 9, 9, 0x20, 0x20, 0x54, 0x74, 9, 9, 0, 0, 1.0f, 1.0f);
        GFX_COMMAND(gFrontendDisplayList++, 0xFD100000U, BUNDLE_ENTRY(11));
        GFX_COMMAND(gFrontendDisplayList++, 0xE8000000U, 0);
        GFX_COMMAND(gFrontendDisplayList++, 0xF5000100U, 0x07000000);
        GFX_COMMAND(gFrontendDisplayList++, 0xE6000000U, 0);
        GFX_COMMAND(gFrontendDisplayList++, 0xF0000000U, 0x073FC000);
        GFX_COMMAND(gFrontendDisplayList++, 0xE7000000U, 0);
        draw_paletted_image(&gFrontendDisplayList, (u8 *)(BUNDLE_ENTRY(11) + 0x200), 2, 1, 9, 9, 0x20, 0x20, 0x54, 0x92, 9, 9, 0, 0, 1.0f, 1.0f);
        begin_text_draw(&gFrontendDisplayList);
        set_texture_draw_color(0xC8, 0xC8, 0x14, 0xA0);
        select_texture_draw_entry(3);
        set_texture_draw_position(0x67, 0x56);
        draw_text(&gFrontendDisplayList, "HIGHLIGHT TERRITORY");
        set_texture_draw_position(0x67, 0x65);
        draw_text(&gFrontendDisplayList, "PREVIOUS SCREEN");
        set_texture_draw_position(0x67, 0x74);
        draw_text(&gFrontendDisplayList, "SELECT");
        set_texture_draw_position(0x67, 0x92);
        draw_text(&gFrontendDisplayList, "EXIT HELP");
    }
    GFX_COMMAND(gFrontendDisplayList++, 0xFCFFFFFFU, 0xFFFCF279U);
    GFX_COMMAND(gFrontendDisplayList++, 0xBA000E02U, 0x8000);
    GFX_COMMAND(gFrontendDisplayList++, 0xB900031DU, 0x00504240);
    GFX_COMMAND(gFrontendDisplayList++, 0xFD100000U, BUNDLE_ENTRY(11));
    GFX_COMMAND(gFrontendDisplayList++, 0xE8000000U, 0);
    GFX_COMMAND(gFrontendDisplayList++, 0xF5000100U, 0x07000000);
    GFX_COMMAND(gFrontendDisplayList++, 0xE6000000U, 0);
    GFX_COMMAND(gFrontendDisplayList++, 0xF0000000U, 0x073FC000);
    GFX_COMMAND(gFrontendDisplayList++, 0xE7000000U, 0);
    draw_paletted_image(&gFrontendDisplayList, (u8 *)(BUNDLE_ENTRY(11) + 0x200), 2, 1, 9, 9, 0x20, 0x20, 0x24, 0xCE, 9, 9, 0, 0, 1.0f, 1.0f);
    select_audio_mode(mode);
}
