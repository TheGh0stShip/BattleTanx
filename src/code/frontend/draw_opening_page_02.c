#include "types.h"

typedef struct Gfx {
    u32 w0;
    u32 w1;
} Gfx;

#define GFX_COMMAND(packet, first, second) { \
    Gfx *command = (packet); \
    command->w0 = (first); \
    command->w1 = (second); \
}

extern Gfx *gFrontendDisplayList __asm__("D_803276D4");
extern s32 gResourceTarget __asm__("D_803275F4");
extern u8 D_8013246C[];
extern s32 gStoryFadeColorA __asm__("D_80327764");
extern s32 gStoryFadeColorB __asm__("D_80327760");
extern void draw_paletted_image(Gfx **list, u8 *texels, s32 arg2, s32 arg3, s32 width, s32 height, s32 tileWidth,
                                s32 tileHeight, s32 x, s32 y, s32 width2, s32 height2, s32 s, s32 t,
                                f32 scaleX, f32 scaleY) __asm__("func_800F3D40");
extern void begin_text_draw(Gfx **gfx) __asm__("func_8010698C");
extern void set_texture_draw_color(s32 red, s32 green, s32 blue, s32 alpha) __asm__("func_8010555C");
extern void set_texture_draw_position(s32 x, s32 y) __asm__("func_8010552C");
extern void draw_text_lines_centered(void *context, u8 *text, s32 lineCount, s32 lineHeight, s32 left,
                                     s32 right) __asm__("func_80105D90");
extern void draw_filled_rectangle(Gfx **list, s32 left, s32 top, s32 right, s32 bottom, s32 red, s32 green,
                                  s32 blue, s32 alpha) __asm__("func_800F4DFC");

typedef struct ResourceBundle {
    s32 count;
    s32 entryOffset[1];
} ResourceBundle;

#define BUNDLE_ENTRY(index) (((ResourceBundle *)gResourceTarget)->entryOffset[index] + gResourceTarget)

void draw_opening_page_02(void) __asm__("func_800AD5A0");

void draw_opening_page_02(void) {
    GFX_COMMAND(gFrontendDisplayList++, 0xB900031DU, 0x00504240);
    GFX_COMMAND(gFrontendDisplayList++, 0xBA000E02U, 0x8000);
    GFX_COMMAND(gFrontendDisplayList++, 0xFC119623U, 0xFF2FFFFFU);
    GFX_COMMAND(gFrontendDisplayList++, 0xFA000101U, 0xFFFFFFFFU);
    GFX_COMMAND(gFrontendDisplayList++, 0xFD100000U, BUNDLE_ENTRY(1));
    GFX_COMMAND(gFrontendDisplayList++, 0xE8000000U, 0);
    GFX_COMMAND(gFrontendDisplayList++, 0xF5000100U, 0x07000000);
    GFX_COMMAND(gFrontendDisplayList++, 0xE6000000U, 0);
    GFX_COMMAND(gFrontendDisplayList++, 0xF0000000U, 0x073FC000);
    GFX_COMMAND(gFrontendDisplayList++, 0xE7000000U, 0);
    draw_paletted_image(&gFrontendDisplayList, (u8 *)(BUNDLE_ENTRY(1) + 0x200), 2, 1, 252, 114, 0x20, 0x20,
                        34, 19, 252, 114, 0, 0, 1.0f, 1.0f);
    begin_text_draw(&gFrontendDisplayList);
    set_texture_draw_color(200, 200, 200, 255);
    set_texture_draw_position(0, 150);
    draw_text_lines_centered(&gFrontendDisplayList, D_8013246C, 1, 12, 0, 320);
    draw_filled_rectangle(&gFrontendDisplayList, 0, 0, 320, 240, 0, 0, 0, gStoryFadeColorA);
    draw_filled_rectangle(&gFrontendDisplayList, 0, 0, 320, 240, 0, 0, 0, gStoryFadeColorB);
}
