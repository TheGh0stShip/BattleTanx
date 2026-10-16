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

#define OPTION_COLOR(index) \
    if (D_80134E60 == (index)) { \
        red = 255; \
        green = 80; \
    } else { \
        red = 150; \
        green = 10; \
    } \
    set_texture_draw_color(red, green, 0, 255)

extern Gfx *gFrontendDisplayList __asm__("D_803276D4");
extern s32 gResourceTarget __asm__("D_803275F4");
extern s32 D_803275F8;
extern s32 D_80327614;
extern s32 D_80327674;
extern s32 D_80125790;
extern s32 D_80125794;
extern s32 D_80134E60;
extern u8 D_80134E64;
extern u8 D_80134E65;
extern u8 D_80134E66;
extern u8 D_80134E67;
extern u8 D_80134E69;

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
extern void draw_text_right_aligned(Gfx **gfx, char *text, s32 right, s32 y) __asm__("func_80105F24");

void draw_options_screen(s32 unused) __asm__("func_800CC4E4");

void draw_options_screen(s32 unused)
{
    s32 mode;
    s32 red;
    s32 green;
    s32 knob;
    s32 base;

    base = D_803275F8;
    draw_filled_rectangle(&gFrontendDisplayList, (base < 0) ? 0 : base, 0x46, base + 320, 0xAA, 0, 0, 0, 0xFF);
    mode = select_audio_mode(0);
    GFX_COMMAND(gFrontendDisplayList++, 0xE7000000U, 0);
    GFX_COMMAND(gFrontendDisplayList++, 0xBA001402U, 0);
    GFX_COMMAND(gFrontendDisplayList++, 0xBA000602U, 0x40);
    GFX_COMMAND(gFrontendDisplayList++, 0xBA000402U, 0x20);
    GFX_COMMAND(gFrontendDisplayList++, 0xB900031DU, 0x0F0A4000);
    GFX_COMMAND(gFrontendDisplayList++, 0xFCFFFFFFU, 0xFFFCF279U);
    GFX_COMMAND(gFrontendDisplayList++, 0xBB000001U, 0x10001000);
    GFX_COMMAND(gFrontendDisplayList++, 0xBA001301U, 0);
    GFX_COMMAND(gFrontendDisplayList++, 0xBA001001U, 0);
    GFX_COMMAND(gFrontendDisplayList++, 0xBA001102U, 0);
    GFX_COMMAND(gFrontendDisplayList++, 0xBA000E02U, 0x8000);
    if (D_80327674 != 0) {
        LOAD_BUNDLE_PALETTE(13);
        draw_paletted_image(&gFrontendDisplayList, (u8 *)(BUNDLE_ENTRY(13) + 0x200), 2, 1, 320, 0x46, 0x20, 0x20, 0,
                            0, 320, 0x46, 0, 0, 1.0f, 1.0f);
    }
    GFX_COMMAND(gFrontendDisplayList++, 0xB900031DU, 0x00504240);
    LOAD_BUNDLE_PALETTE(15);
    draw_paletted_image(&gFrontendDisplayList, (u8 *)(BUNDLE_ENTRY(15) + 0x200), 2, 1, 320, 0xB7, 0x20, 0x20,
                        D_803275F8, 0x39, 320, 0xB7, 0, 0, 1.0f, 1.0f);
    select_audio_mode(mode);
    LOAD_BUNDLE_PALETTE(2);
    draw_paletted_image(&gFrontendDisplayList, (u8 *)(BUNDLE_ENTRY(2) + 0x200), 2, 1, 0x71, 0x1E, 0x20, 0x20,
                        D_803275F8 + 0x69, 0x16, 0x71, 0x1E, 0, 0, 1.0f, 1.0f);
    LOAD_BUNDLE_PALETTE(3);
    draw_paletted_image(&gFrontendDisplayList, (u8 *)(BUNDLE_ENTRY(3) + 0x200), 2, 1, 0x6D, 9, 0x20, 0x20,
                        D_803275F8 + 0x33, 0x56, 0x6D, 9, 0, 0, 1.0f, 1.0f);
    LOAD_BUNDLE_PALETTE(4);
    draw_paletted_image(&gFrontendDisplayList, (u8 *)(BUNDLE_ENTRY(4) + 0x200), 2, 1, 0x6D, 9, 0x20, 0x20,
                        D_803275F8 + 0x33, 0x67, 0x6D, 9, 0, 0, 1.0f, 1.0f);
    begin_text_draw(&gFrontendDisplayList);
    select_texture_draw_entry(2);
    OPTION_COLOR(0);
    draw_text_right_aligned(&gFrontendDisplayList, "SFX Volume", D_803275F8 + 0x122, 0x56);
    OPTION_COLOR(1);
    draw_text_right_aligned(&gFrontendDisplayList, "Music Volume", D_803275F8 + 0x122, 0x67);
    OPTION_COLOR(2);
    draw_text_right_aligned(&gFrontendDisplayList, "Difficulty", D_803275F8 + 0x122, 0x78);
    OPTION_COLOR(3);
    draw_text_right_aligned(&gFrontendDisplayList, "Powerups", D_803275F8 + 0x122, 0x89);
    OPTION_COLOR(4);
    draw_text_right_aligned(&gFrontendDisplayList, "Powerup Regen", D_803275F8 + 0x122, 0x9A);
    OPTION_COLOR(5);
    draw_text_right_aligned(&gFrontendDisplayList, "Base Defense", D_803275F8 + 0x122, 0xAB);
    OPTION_COLOR(6);
    draw_text_right_aligned(&gFrontendDisplayList, "Unlimited Ammo", D_803275F8 + 0x122, 0xBC);
    OPTION_COLOR(7);
    draw_text_right_aligned(&gFrontendDisplayList, "Controller Config", D_803275F8 + 0x122, 0xCD);
    knob = D_80125790 * 13;
    base = D_803275F8 + 0x36;
    knob += base;
    GFX_COMMAND(gFrontendDisplayList++, 0xFCFFFFFFU, 0xFFFCF279U);
    GFX_COMMAND(gFrontendDisplayList++, 0xBA000E02U, 0x8000);
    if (D_80134E60 == 0) {
        LOAD_BUNDLE_PALETTE(1);
        draw_paletted_image(&gFrontendDisplayList, (u8 *)(BUNDLE_ENTRY(1) + 0x200), 2, 1, 8, 0xD, 0x20, 0x20, knob,
                            0x55, 8, 0xD, 0, 0, 1.0f, 1.0f);
    } else {
        LOAD_BUNDLE_PALETTE(0);
        draw_paletted_image(&gFrontendDisplayList, (u8 *)(BUNDLE_ENTRY(0) + 0x200), 2, 1, 8, 0xD, 0x20, 0x20, knob,
                            0x55, 8, 0xD, 0, 0, 1.0f, 1.0f);
    }
    knob = D_80125794 * 13;
    base = D_803275F8 + 0x36;
    knob += base;
    if (D_80134E60 == 1) {
        LOAD_BUNDLE_PALETTE(1);
        draw_paletted_image(&gFrontendDisplayList, (u8 *)(BUNDLE_ENTRY(1) + 0x200), 2, 1, 8, 0xD, 0x20, 0x20, knob,
                            0x66, 8, 0xD, 0, 0, 1.0f, 1.0f);
    } else {
        LOAD_BUNDLE_PALETTE(0);
        draw_paletted_image(&gFrontendDisplayList, (u8 *)(BUNDLE_ENTRY(0) + 0x200), 2, 1, 8, 0xD, 0x20, 0x20, knob,
                            0x66, 8, 0xD, 0, 0, 1.0f, 1.0f);
    }
    begin_text_draw(&gFrontendDisplayList);
    set_texture_draw_color(255, 0xAA, 0, 255);
    switch (D_80134E64) {
    case 0:
        draw_text_right_aligned(&gFrontendDisplayList, "Easy", D_803275F8 + 0x82, 0x78);
        break;
    case 1:
        draw_text_right_aligned(&gFrontendDisplayList, "Normal", D_803275F8 + 0x82, 0x78);
        break;
    case 2:
        draw_text_right_aligned(&gFrontendDisplayList, "Hard", D_803275F8 + 0x82, 0x78);
        break;
    }
    if (D_80134E65 != 0) {
        draw_text_right_aligned(&gFrontendDisplayList, "On", D_803275F8 + 0x82, 0x89);
    } else {
        draw_text_right_aligned(&gFrontendDisplayList, "Off", D_803275F8 + 0x82, 0x89);
    }
    if (D_80134E66 != 0) {
        draw_text_right_aligned(&gFrontendDisplayList, "On", D_803275F8 + 0x82, 0x9A);
    } else {
        draw_text_right_aligned(&gFrontendDisplayList, "Off", D_803275F8 + 0x82, 0x9A);
    }
    if (D_80134E67 != 0) {
        draw_text_right_aligned(&gFrontendDisplayList, "On", D_803275F8 + 0x82, 0xAB);
    } else {
        draw_text_right_aligned(&gFrontendDisplayList, "Off", D_803275F8 + 0x82, 0xAB);
    }
    if (D_80134E69 != 0) {
        draw_text_right_aligned(&gFrontendDisplayList, "On", D_803275F8 + 0x82, 0xBC);
    } else {
        draw_text_right_aligned(&gFrontendDisplayList, "Off", D_803275F8 + 0x82, 0xBC);
    }
    set_texture_draw_color(200, 200, 200, 255);
    select_texture_draw_entry(3);
    set_texture_draw_position(D_803275F8 + 0x31, 0xCE);
    draw_text(&gFrontendDisplayList, "HELP");
    mode = select_audio_mode(0);
    if (D_80327614 != 0) {
        draw_filled_rectangle(&gFrontendDisplayList, 0x3E, 0x4C, 0xC3, 0x66, 0, 0, 0, 0xC8);
        GFX_COMMAND(gFrontendDisplayList++, 0xFCFFFFFFU, 0xFFFCF279U);
        GFX_COMMAND(gFrontendDisplayList++, 0xBA000E02U, 0x8000);
        GFX_COMMAND(gFrontendDisplayList++, 0xB900031DU, 0x00504240);
        LOAD_BUNDLE_PALETTE(12);
        draw_paletted_image(&gFrontendDisplayList, (u8 *)(BUNDLE_ENTRY(12) + 0x200), 2, 1, 9, 9, 0x20, 0x20, 0x47,
                            0x56, 9, 9, 0, 0, 1.0f, 1.0f);
        LOAD_BUNDLE_PALETTE(1);
        draw_paletted_image(&gFrontendDisplayList, (u8 *)(BUNDLE_ENTRY(1) + 0x200), 2, 1, 9, 9, 0x20, 0x20, 0x54,
                            0x56, 9, 9, 0, 0, 1.0f, 1.0f);
        LOAD_BUNDLE_PALETTE(6);
        draw_paletted_image(&gFrontendDisplayList, (u8 *)(BUNDLE_ENTRY(6) + 0x200), 2, 1, 9, 9, 0x20, 0x20, 0x47,
                            0x65, 9, 9, 0, 0, 1.0f, 1.0f);
        LOAD_BUNDLE_PALETTE(8);
        draw_paletted_image(&gFrontendDisplayList, (u8 *)(BUNDLE_ENTRY(8) + 0x200), 2, 1, 9, 9, 0x20, 0x20, 0x54,
                            0x65, 9, 9, 0, 0, 1.0f, 1.0f);
        LOAD_BUNDLE_PALETTE(0);
        draw_paletted_image(&gFrontendDisplayList, (u8 *)(BUNDLE_ENTRY(0) + 0x200), 2, 1, 9, 9, 0x20, 0x20, 0x54,
                            0x74, 9, 9, 0, 0, 1.0f, 1.0f);
        LOAD_BUNDLE_PALETTE(10);
        draw_paletted_image(&gFrontendDisplayList, (u8 *)(BUNDLE_ENTRY(10) + 0x200), 2, 1, 9, 9, 0x20, 0x20, 0x54,
                            0x83, 9, 9, 0, 0, 1.0f, 1.0f);
        LOAD_BUNDLE_PALETTE(11);
        draw_paletted_image(&gFrontendDisplayList, (u8 *)(BUNDLE_ENTRY(11) + 0x200), 2, 1, 9, 9, 0x20, 0x20, 0x54,
                            0xA1, 9, 9, 0, 0, 1.0f, 1.0f);
        begin_text_draw(&gFrontendDisplayList);
        set_texture_draw_color(200, 200, 0x14, 0xA0);
        select_texture_draw_entry(3);
        set_texture_draw_position(0x76, 0x56);
        draw_text(&gFrontendDisplayList, "HIGHLIGHT OPTION");
        set_texture_draw_position(0x76, 0x65);
        draw_text(&gFrontendDisplayList, "CHANGE OPTION");
        set_texture_draw_position(0x76, 0x74);
        draw_text(&gFrontendDisplayList, "PREVIOUS SCREEN");
        set_texture_draw_position(0x76, 0x83);
        draw_text(&gFrontendDisplayList, "SELECT");
        set_texture_draw_position(0x76, 0xA1);
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
