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

#define MENU_ITEM_COLOR(index) \
    if (D_80134E54 == (index)) { \
        set_texture_draw_color(255, 80, 0, 255); \
    } else { \
        set_texture_draw_color(150, 10, 0, 255); \
    }

extern Gfx *gFrontendDisplayList __asm__("D_803276D4");
extern s32 gResourceTarget __asm__("D_803275F4");
extern s32 D_803275F8;
extern s32 D_80327614;
extern s32 D_80327674;
extern u8 D_80134BE0[];
extern u8 D_80134DE0[];
extern s32 D_80134E54;
extern s32 D_80134E58;
extern s32 D_80134E5C;
extern u8 D_80134E74;
extern char *D_80134E40[];
extern u8 D_80135766;

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
extern void draw_number(Gfx **gfx, s64 value) __asm__("func_801055D4");

void draw_main_menu_screen(void) __asm__("func_800CAA04");

void draw_main_menu_screen(void)
{
    s32 left;
    s32 mode;

    left = D_803275F8;
    GFX_COMMAND(gFrontendDisplayList++, 0xE7000000U, 0);
    GFX_COMMAND(gFrontendDisplayList++, 0xBA001402U, 0);
    GFX_COMMAND(gFrontendDisplayList++, 0xFCFFFFFFU, 0xFFFCF279U);
    GFX_COMMAND(gFrontendDisplayList++, 0xB900031DU, 0x0F0A4000);
    GFX_COMMAND(gFrontendDisplayList++, 0xBA001301U, 0);
    GFX_COMMAND(gFrontendDisplayList++, 0xBA001001U, 0);
    GFX_COMMAND(gFrontendDisplayList++, 0xBA000C02U, 0);
    GFX_COMMAND(gFrontendDisplayList++, 0xBA000903U, 0xC00);
    GFX_COMMAND(gFrontendDisplayList++, 0xBA000E02U, 0x8000);
    draw_filled_rectangle(&gFrontendDisplayList, (left < 0) ? 0 : left, 0x46, left + 320, 0xAA, 0, 0, 0, 0xFF);
    GFX_COMMAND(gFrontendDisplayList++, 0xFCFFFFFFU, 0xFFFCF279U);
    GFX_COMMAND(gFrontendDisplayList++, 0xBA000E02U, 0x8000);
    mode = select_audio_mode(0);
    if (D_80327674 != 0) {
        LOAD_BUNDLE_PALETTE(13);
        draw_paletted_image(&gFrontendDisplayList, (u8 *)(BUNDLE_ENTRY(13) + 0x200), 2, 1, 320, 0x46, 0x20, 0x20, 0,
                            0, 320, 0x46, 0, 0, 1.0f, 1.0f);
    }
    GFX_COMMAND(gFrontendDisplayList++, 0xB900031DU, 0x00504240);
    LOAD_BUNDLE_PALETTE(14);
    draw_paletted_image(&gFrontendDisplayList, (u8 *)(BUNDLE_ENTRY(14) + 0x200), 2, 1, 320, 0xB7, 0x20, 0x20,
                        D_803275F8, 0x39, 320, 0xB7, 0, 0, 1.0f, 1.0f);
    select_audio_mode(mode);
    LOAD_BUNDLE_PALETTE(0);
    draw_paletted_image(&gFrontendDisplayList, (u8 *)(BUNDLE_ENTRY(0) + 0x200), 2, 1, 0xA6, 0x1E, 0x20, 0x20,
                        D_803275F8 + 0x4D, 0x16, 0xA6, 0x1E, 0, 0, 1.0f, 1.0f);
    begin_text_draw(&gFrontendDisplayList);
    select_texture_draw_entry(2);
    MENU_ITEM_COLOR(0)
    set_texture_draw_position(D_803275F8 + 0x34, 0x4F);
    draw_text(&gFrontendDisplayList, "Players");
    MENU_ITEM_COLOR(1)
    set_texture_draw_position(D_803275F8 + 0x34, 0x60);
    draw_text(&gFrontendDisplayList, "Playmode");
    MENU_ITEM_COLOR(2)
    set_texture_draw_position(D_803275F8 + 0x34, 0x71);
    draw_text(&gFrontendDisplayList, "Options");
    MENU_ITEM_COLOR(4)
    set_texture_draw_position(D_803275F8 + 0x34, 0x93);
    draw_text(&gFrontendDisplayList, "Input Code");
    if (D_80134E74 == 0 || D_80134E5C != 0) {
        set_texture_draw_color(0x40, 0x40, 0x40, 255);
    } else MENU_ITEM_COLOR(5)
    set_texture_draw_position(D_803275F8 + 0x34, 0xA4);
    draw_text(&gFrontendDisplayList, "Load Game");
    MENU_ITEM_COLOR(6)
    set_texture_draw_position(D_803275F8 + 0x34, 0xB5);
    draw_text(&gFrontendDisplayList, "Start Game");
    MENU_ITEM_COLOR(3)
    set_texture_draw_position(D_803275F8 + 0x34, 0x82);
    draw_text(&gFrontendDisplayList, "Credits");
    set_texture_draw_color(255, 0xAA, 0, 255);
    set_texture_draw_position(D_803275F8 + 0xB8, 0x4F);
    draw_number(&gFrontendDisplayList, D_80134E58);
    set_texture_draw_position(D_803275F8 + 0xB8, 0x60);
    draw_text(&gFrontendDisplayList, D_80134E40[D_80134E5C]);
    set_texture_draw_color(200, 200, 200, 255);
    select_texture_draw_entry(3);
    set_texture_draw_position(D_803275F8 + 0x31, 0xCE);
    draw_text(&gFrontendDisplayList, "HELP");
    if (D_80135766 != 0) {
        GFX_COMMAND(gFrontendDisplayList++, 0xFD100000U, D_80134DE0);
        GFX_COMMAND(gFrontendDisplayList++, 0xE8000000U, 0);
        GFX_COMMAND(gFrontendDisplayList++, 0xF5000100U, 0x07000000);
        GFX_COMMAND(gFrontendDisplayList++, 0xE6000000U, 0);
        GFX_COMMAND(gFrontendDisplayList++, 0xF0000000U, 0x0703C000);
        GFX_COMMAND(gFrontendDisplayList++, 0xE7000000U, 0);
        GFX_COMMAND(gFrontendDisplayList++, 0xFD500000U, D_80134BE0);
        GFX_COMMAND(gFrontendDisplayList++, 0xF5500000U, 0x07000200);
        GFX_COMMAND(gFrontendDisplayList++, 0xE6000000U, 0);
        GFX_COMMAND(gFrontendDisplayList++, 0xF3000000U, 0x070FF200);
        GFX_COMMAND(gFrontendDisplayList++, 0xE7000000U, 0);
        GFX_COMMAND(gFrontendDisplayList++, 0xF5400800U, 0x200);
        GFX_COMMAND(gFrontendDisplayList++, 0xF2000000U, 0x000FC03C);
        GFX_COMMAND(gFrontendDisplayList++, 0xE4000000U | ((((D_803275F8 + 0x5E) << 2) & 0xFFF) << 12) | 0x130,
                    ((((D_803275F8 + 0x1E) << 2) & 0xFFF) << 12) | 0xF0);
        GFX_COMMAND(gFrontendDisplayList++, 0xB4000000U, 0);
        GFX_COMMAND(gFrontendDisplayList++, 0xB3000000U, 0x04000400);
    }
    mode = select_audio_mode(0);
    begin_text_draw(&gFrontendDisplayList);
    set_texture_draw_color(200, 200, 0x14, 0xA0);
    select_texture_draw_entry(3);
    if (D_80327614 != 0) {
        draw_filled_rectangle(&gFrontendDisplayList, 0x3E, 0x4C, 0xC3, 0x55, 0, 0, 0, 0xC8);
        GFX_COMMAND(gFrontendDisplayList++, 0xFCFFFFFFU, 0xFFFCF279U);
        GFX_COMMAND(gFrontendDisplayList++, 0xBA000E02U, 0x8000);
        GFX_COMMAND(gFrontendDisplayList++, 0xB900031DU, 0x00504240);
        LOAD_BUNDLE_PALETTE(12);
        draw_paletted_image(&gFrontendDisplayList, (u8 *)(BUNDLE_ENTRY(12) + 0x200), 2, 1, 9, 9, 0x20, 0x20, 0x56,
                            0x56, 9, 9, 0, 0, 1.0f, 1.0f);
        LOAD_BUNDLE_PALETTE(1);
        draw_paletted_image(&gFrontendDisplayList, (u8 *)(BUNDLE_ENTRY(1) + 0x200), 2, 1, 9, 9, 0x20, 0x20, 0x63,
                            0x56, 9, 9, 0, 0, 1.0f, 1.0f);
        LOAD_BUNDLE_PALETTE(6);
        draw_paletted_image(&gFrontendDisplayList, (u8 *)(BUNDLE_ENTRY(6) + 0x200), 2, 1, 9, 9, 0x20, 0x20, 0x56,
                            0x65, 9, 9, 0, 0, 1.0f, 1.0f);
        LOAD_BUNDLE_PALETTE(8);
        draw_paletted_image(&gFrontendDisplayList, (u8 *)(BUNDLE_ENTRY(8) + 0x200), 2, 1, 9, 9, 0x20, 0x20, 0x63,
                            0x65, 9, 9, 0, 0, 1.0f, 1.0f);
        LOAD_BUNDLE_PALETTE(10);
        draw_paletted_image(&gFrontendDisplayList, (u8 *)(BUNDLE_ENTRY(10) + 0x200), 2, 1, 9, 9, 0x20, 0x20, 0x63,
                            0x74, 9, 9, 0, 0, 1.0f, 1.0f);
        LOAD_BUNDLE_PALETTE(11);
        draw_paletted_image(&gFrontendDisplayList, (u8 *)(BUNDLE_ENTRY(11) + 0x200), 2, 1, 9, 9, 0x20, 0x20, 0x63,
                            0x92, 9, 9, 0, 0, 1.0f, 1.0f);
        begin_text_draw(&gFrontendDisplayList);
        set_texture_draw_color(200, 200, 0x14, 0xA0);
        select_texture_draw_entry(3);
        set_texture_draw_position(0x76, 0x56);
        draw_text(&gFrontendDisplayList, "HIGHLIGHT OPTION");
        set_texture_draw_position(0x76, 0x65);
        draw_text(&gFrontendDisplayList, "CHANGE OPTION");
        set_texture_draw_position(0x76, 0x74);
        draw_text(&gFrontendDisplayList, "SELECT");
        set_texture_draw_position(0x76, 0x92);
        draw_text(&gFrontendDisplayList, "EXIT HELP");
    }
    GFX_COMMAND(gFrontendDisplayList++, 0xFCFFFFFFU, 0xFFFCF279U);
    GFX_COMMAND(gFrontendDisplayList++, 0xBA000E02U, 0x8000);
    GFX_COMMAND(gFrontendDisplayList++, 0xB900031DU, 0x00504240);
    LOAD_BUNDLE_PALETTE(11);
    draw_paletted_image(&gFrontendDisplayList, (u8 *)(BUNDLE_ENTRY(11) + 0x200), 2, 1, 9, 9, 0x20, 0x20,
                        D_803275F8 + 0x24, 0xCE, 9, 9, 0, 0, 1.0f, 1.0f);
    select_audio_mode(mode);
}
