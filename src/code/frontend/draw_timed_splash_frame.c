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

extern Gfx *gFrontendDisplayList __asm__("D_803276D4");
extern s32 gResourceTarget __asm__("D_803275F4");
extern void draw_paletted_image(Gfx **list, u8 *texels, s32 arg2, s32 arg3, s32 width, s32 height, s32 tileWidth,
                                s32 tileHeight, s32 x, s32 y, s32 width2, s32 height2, s32 s, s32 t,
                                f32 scaleX, f32 scaleY) __asm__("func_800F3D40");
extern void draw_filled_rectangle(Gfx **list, s32 left, s32 top, s32 right, s32 bottom, s32 red, s32 green, s32 blue, s32 alpha) __asm__("func_800F4DFC");
extern void begin_text_draw(Gfx **gfx) __asm__("func_8010698C");
extern void set_texture_draw_color(s32 red, s32 green, s32 blue, s32 alpha) __asm__("func_8010555C");
extern void select_texture_draw_entry(s32 index) __asm__("func_801054E0");
extern void set_texture_draw_position(s32 x, s32 y) __asm__("func_8010552C");
extern void draw_text_in_span(Gfx **gfx, char *text, s32 left, s32 right) __asm__("func_80105A50");
extern u8 gFrontendScreenFlag __asm__("D_80328280");
extern u8 D_80134E80[];
extern u8 D_80134E8C[];
extern u8 D_80134EB8[];
extern u8 D_80134EE4[];
extern u8 D_80134F10[];
extern u8 D_80134F3C[];
extern u8 D_80134F6C[];
extern u8 D_80134F9C[];

void draw_timed_splash_frame(void) __asm__("func_800D0DAC");

void draw_timed_splash_frame(void) {
    draw_filled_rectangle(&gFrontendDisplayList, 0, 0, 320, 240, 0, 0, 0, 255);
    GFX_COMMAND(gFrontendDisplayList++, 0xe7000000U, 0x0U);
    GFX_COMMAND(gFrontendDisplayList++, 0xba001402U, 0x0U);
    GFX_COMMAND(gFrontendDisplayList++, 0xfcffffffU, 0xfffcf279U);
    GFX_COMMAND(gFrontendDisplayList++, 0xb900031dU, 0xf0a4000U);
    GFX_COMMAND(gFrontendDisplayList++, 0xba001301U, 0x0U);
    GFX_COMMAND(gFrontendDisplayList++, 0xba001001U, 0x0U);
    GFX_COMMAND(gFrontendDisplayList++, 0xba000c02U, 0x0U);
    GFX_COMMAND(gFrontendDisplayList++, 0xba000903U, 0xc00U);
    GFX_COMMAND(gFrontendDisplayList++, 0xba000e02U, 0x8000U);
    GFX_COMMAND(gFrontendDisplayList++, 0xfcffffffU, 0xfffcf279U);
    GFX_COMMAND(gFrontendDisplayList++, 0xba000e02U, 0x8000U);
    if (gFrontendScreenFlag == 0) {
    GFX_COMMAND(gFrontendDisplayList++, 0xfd100000U, BUNDLE_ENTRY(0));
    GFX_COMMAND(gFrontendDisplayList++, 0xe8000000U, 0x0U);
    GFX_COMMAND(gFrontendDisplayList++, 0xf5000100U, 0x7000000U);
    GFX_COMMAND(gFrontendDisplayList++, 0xe6000000U, 0x0U);
    GFX_COMMAND(gFrontendDisplayList++, 0xf0000000U, 0x73fc000U);
    GFX_COMMAND(gFrontendDisplayList++, 0xe7000000U, 0x0U);
    draw_paletted_image(&gFrontendDisplayList, (u8 *)(BUNDLE_ENTRY(0) + 0x200), 0x2, 0x1, 0xb4, 0x3e, 0x20, 0x20, 0x46, 0x59, 0xb4, 0x3e, 0x0, 0x0, 1.0f, 1.0f);
    } else {
    begin_text_draw(&gFrontendDisplayList);
    set_texture_draw_color(200, 200, 200, 255);
    select_texture_draw_entry(1);
    set_texture_draw_position(30, 115);
    draw_text_in_span(&gFrontendDisplayList, D_80134E80, 0, 320);
    set_texture_draw_position(30, 127);
    draw_text_in_span(&gFrontendDisplayList, D_80134E8C, 0, 320);
    set_texture_draw_position(30, 139);
    draw_text_in_span(&gFrontendDisplayList, D_80134EB8, 0, 320);
    set_texture_draw_position(30, 151);
    draw_text_in_span(&gFrontendDisplayList, D_80134EE4, 0, 320);
    set_texture_draw_position(30, 163);
    draw_text_in_span(&gFrontendDisplayList, D_80134F10, 0, 320);
    set_texture_draw_position(30, 175);
    draw_text_in_span(&gFrontendDisplayList, D_80134F3C, 0, 320);
    set_texture_draw_position(30, 187);
    draw_text_in_span(&gFrontendDisplayList, D_80134F6C, 0, 320);
    set_texture_draw_position(30, 199);
    draw_text_in_span(&gFrontendDisplayList, D_80134F9C, 0, 320);
    }
}
