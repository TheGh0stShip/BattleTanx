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

#define DRAW_BUNDLE_IMAGE(index, w, h, x, y) \
    LOAD_BUNDLE_PALETTE(index); \
    draw_paletted_image(&gFrontendDisplayList, (u8 *)(BUNDLE_ENTRY(index) + 0x200), 2, 1, (w), (h), 0x20, 0x20, \
                        (x), (y), (w), (h), 0, 0, 1.0f, 1.0f)

#define TEAM_PRIM_COLOR(team) \
    GFX_COMMAND(gFrontendDisplayList++, 0xFA000101U, \
                ((u32)(u8)gTeamRed[team] << 24) | ((u32)(u8)gTeamGreen[team] << 16) | \
                ((u32)(u8)gTeamBlue[team] << 8) | 0xFF)

extern Gfx *gFrontendDisplayList __asm__("D_803276D4");
extern s32 gResourceTarget __asm__("D_803275F4");
extern s32 D_80327614;
extern s32 gControllerSlotCount __asm__("D_80134E58");
extern s32 gMenuOptions[4] __asm__("D_80328400");
extern s32 gSlotState[4] __asm__("D_803283C8");
extern s32 D_803283E8;
extern s32 gSlotChoice[4] __asm__("D_803283F0");
extern s32 gSlotRole[4] __asm__("D_801262C0");
extern char *gRoleNames[] __asm__("D_80135210");
extern char *gTeamNames[] __asm__("D_80135224");
extern s32 gTeamRed[5] __asm__("D_80135238");
extern s32 gTeamGreen[5] __asm__("D_8013524C");
extern s32 gTeamBlue[5] __asm__("D_80135260");
extern s32 gSlotLeft[4] __asm__("D_80135274");
extern s32 gSlotRight[4] __asm__("D_80135284");
extern s32 gSlotTop[4] __asm__("D_80135294");

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

void draw_team_select_screen(void) __asm__("func_800D6BC0");

void draw_team_select_screen(void)
{
    s32 row;
    s32 col;
    s32 i;
    s32 mode;
    u8 nameRed, nameGreen, nameBlue;
    u8 onRed, onGreen, onBlue;
    u8 offRed, offGreen, offBlue;

    draw_filled_rectangle(&gFrontendDisplayList, 0, 0, 320, 240, 0, 0, 0, 0xFF);
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
    LOAD_BUNDLE_PALETTE(9);
    for (i = 0; i < 4; i++) {
        for (col = 0; col < 6; col++) {
            draw_paletted_image(&gFrontendDisplayList, (u8 *)(BUNDLE_ENTRY(9) + 0x200), 2, 1, 0x40, 0x40, 0x20, 0x20,
                                col << 6, i << 6, 0x40, 0x40, 0, 0, 1.0f, 1.0f);
        }
    }
    DRAW_BUNDLE_IMAGE(7, 0x114, 8, 0x16, 0xE);
    DRAW_BUNDLE_IMAGE(4, 0x114, 8, 0x16, 0x39);
    DRAW_BUNDLE_IMAGE(4, 0x114, 8, 0x16, 0xD9);
    DRAW_BUNDLE_IMAGE(5, 8, 0xC3, 0x16, 0x16);
    DRAW_BUNDLE_IMAGE(6, 8, 0xC3, 0x122, 0x16);
    GFX_COMMAND(gFrontendDisplayList++, 0xFC119623U, 0xFF2FFFFFU);
    i = gMenuOptions[0];
    TEAM_PRIM_COLOR(i);
    DRAW_BUNDLE_IMAGE(0, 0x71, 0x3F, 0x2F, 0x41);
    i = gMenuOptions[1];
    TEAM_PRIM_COLOR(i);
    DRAW_BUNDLE_IMAGE(1, 0x71, 0x3F, 0xA0, 0x41);
    i = gMenuOptions[2];
    TEAM_PRIM_COLOR(i);
    DRAW_BUNDLE_IMAGE(3, 0x71, 0x3F, 0x2F, 0x80);
    i = gMenuOptions[3];
    TEAM_PRIM_COLOR(i);
    DRAW_BUNDLE_IMAGE(2, 0x71, 0x3F, 0xA0, 0x80);
    begin_text_draw(&gFrontendDisplayList);
    select_texture_draw_entry(3);
    for (i = 0; i < 4; i++) {
        onRed = 0xFF;
        onGreen = 0x50;
        onBlue = 0;
        offRed = 0x96;
        offGreen = 0xA;
        offBlue = 0;
        nameRed = 0xC8;
        nameGreen = 0xC8;
        nameBlue = 0xC8;
        if ((i == 0 && D_803283E8 != -2)
            || (i < gControllerSlotCount ? gSlotState[i] != 0 : (gSlotState[0] != 0 || i != D_803283E8))) {
            onRed = 0x64;
            onGreen = 0x64;
            onBlue = 0x64;
            offRed = 0x64;
            offGreen = 0x64;
            offBlue = 0x64;
            nameRed = 0x64;
            nameGreen = 0x64;
            nameBlue = 0x64;
        }
        set_texture_draw_position(0, gSlotTop[i]);
        set_texture_draw_color(nameRed, nameGreen, nameBlue, 0xFF);
        if (i < gControllerSlotCount) {
            draw_text_in_span(&gFrontendDisplayList, "HUMAN", gSlotLeft[i], gSlotRight[i]);
        } else {
            draw_text_in_span(&gFrontendDisplayList, "COMPUTER", gSlotLeft[i], gSlotRight[i]);
        }
        set_texture_draw_position(0, gSlotTop[i] + 0x11);
        if (gSlotChoice[i] == 0) {
            set_texture_draw_color(onRed, onGreen, onBlue, 0xFF);
        } else {
            set_texture_draw_color(offRed, offGreen, offBlue, 0xFF);
        }
        draw_text_in_span(&gFrontendDisplayList, gRoleNames[gSlotRole[i]], gSlotLeft[i], gSlotRight[i]);
        set_texture_draw_position(0, gSlotTop[i] + 0x1E);
        if (gSlotChoice[i] == 1) {
            set_texture_draw_color(onRed, onGreen, onBlue, 0xFF);
        } else {
            set_texture_draw_color(offRed, offGreen, offBlue, 0xFF);
        }
        draw_text_in_span(&gFrontendDisplayList, gTeamNames[gMenuOptions[i]], gSlotLeft[i], gSlotRight[i]);
    }
    GFX_COMMAND(gFrontendDisplayList++, 0xFCFFFFFFU, 0xFFFCF279U);
    GFX_COMMAND(gFrontendDisplayList++, 0xBA000E02U, 0x8000);
    GFX_COMMAND(gFrontendDisplayList++, 0xB900031DU, 0x00504240);
    DRAW_BUNDLE_IMAGE(8, 0xD4, 0x1B, 0x36, 0x18);
    begin_text_draw(&gFrontendDisplayList);
    set_texture_draw_color(200, 200, 200, 0xFF);
    select_texture_draw_entry(3);
    set_texture_draw_position(0x31, 0xCE);
    draw_text(&gFrontendDisplayList, "HELP");
    mode = select_audio_mode(0);
    if (D_80327614 != 0) {
        draw_filled_rectangle(&gFrontendDisplayList, 0x3E, 0x4C, 0xC3, 0x69, 0, 0, 0, 0xC8);
        GFX_COMMAND(gFrontendDisplayList++, 0xFCFFFFFFU, 0xFFFCF279U);
        GFX_COMMAND(gFrontendDisplayList++, 0xBA000E02U, 0x8000);
        GFX_COMMAND(gFrontendDisplayList++, 0xB900031DU, 0x00504240);
        DRAW_BUNDLE_IMAGE(7, 9, 9, 0x53, 0x52);
        DRAW_BUNDLE_IMAGE(9, 9, 9, 0x60, 0x52);
        DRAW_BUNDLE_IMAGE(12, 9, 9, 0x53, 0x61);
        DRAW_BUNDLE_IMAGE(1, 9, 9, 0x60, 0x61);
        DRAW_BUNDLE_IMAGE(6, 9, 9, 0x53, 0x70);
        DRAW_BUNDLE_IMAGE(8, 9, 9, 0x60, 0x70);
        DRAW_BUNDLE_IMAGE(0, 9, 9, 0x60, 0x7F);
        DRAW_BUNDLE_IMAGE(10, 9, 9, 0x60, 0x8E);
        DRAW_BUNDLE_IMAGE(11, 9, 9, 0x60, 0xA5);
        begin_text_draw(&gFrontendDisplayList);
        set_texture_draw_color(200, 200, 0x14, 0xA0);
        select_texture_draw_entry(3);
        set_texture_draw_position(0x73, 0x52);
        draw_text(&gFrontendDisplayList, "CHOOSE TEAM");
        set_texture_draw_position(0x73, 0x61);
        draw_text(&gFrontendDisplayList, "HIGHLIGHT OPTION");
        set_texture_draw_position(0x73, 0x70);
        draw_text(&gFrontendDisplayList, "CHANGE OPTION");
        set_texture_draw_position(0x73, 0x7F);
        draw_text(&gFrontendDisplayList, "PREVIOUS SCREEN");
        set_texture_draw_position(0x73, 0x8E);
        draw_text(&gFrontendDisplayList, "DONE");
        set_texture_draw_position(0x73, 0xA5);
        draw_text(&gFrontendDisplayList, "EXIT HELP");
    }
    GFX_COMMAND(gFrontendDisplayList++, 0xFCFFFFFFU, 0xFFFCF279U);
    GFX_COMMAND(gFrontendDisplayList++, 0xBA000E02U, 0x8000);
    GFX_COMMAND(gFrontendDisplayList++, 0xB900031DU, 0x00504240);
    DRAW_BUNDLE_IMAGE(11, 9, 9, 0x24, 0xCE);
    select_audio_mode(mode);
}
