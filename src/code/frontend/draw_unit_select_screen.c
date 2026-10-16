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

#define LOAD_PALETTE(addr, tlut) \
    GFX_COMMAND(gFrontendDisplayList++, 0xFD100000U, (addr)); \
    GFX_COMMAND(gFrontendDisplayList++, 0xE8000000U, 0); \
    GFX_COMMAND(gFrontendDisplayList++, 0xF5000100U, 0x07000000); \
    GFX_COMMAND(gFrontendDisplayList++, 0xE6000000U, 0); \
    GFX_COMMAND(gFrontendDisplayList++, 0xF0000000U, (tlut)); \
    GFX_COMMAND(gFrontendDisplayList++, 0xE7000000U, 0)

#define DRAW_IMAGE(index, w, h, x, y, scale) \
    LOAD_PALETTE(BUNDLE_ENTRY(index), 0x073FC000); \
    draw_paletted_image(&gFrontendDisplayList, (u8 *)(BUNDLE_ENTRY(index) + 0x200), 2, 1, (w), (h), 0x20, 0x20, \
                        (x), (y), (w), (h), 0, 0, (scale), (scale))

#define DRAW_ENTRY_IMAGE(entry, w, h, x, y, w2, h2, scale) \
    LOAD_PALETTE(((s32 *)gResourceTarget)[entry] + gResourceTarget, 0x073FC000); \
    draw_paletted_image(&gFrontendDisplayList, \
                        (u8 *)(((s32 *)gResourceTarget)[entry] + gResourceTarget + 0x200), 2, 1, (w), (h), \
                        0x20, 0x20, (x), (y), (w2), (h2), 0, 0, (scale), (scale))

#define SET_COMBINE_SHADE() GFX_COMMAND(gFrontendDisplayList++, 0xFCFFFFFFU, 0xFFFCF279U)

extern Gfx *gFrontendDisplayList __asm__("D_803276D4");
extern s32 gResourceTarget __asm__("D_803275F4");
extern u16 D_80133FE0;
extern s32 D_80134010[];
extern s32 D_80134030[];
extern u8 *D_80134960[];
extern f32 D_80134988[][4];
extern s32 D_80134A28[];
extern s32 D_80134A50[];
extern s32 D_80327EE8;
extern s32 D_80327EEC;
extern u8 D_80327EEF;
extern s32 D_80327EF0;

extern f32 angle_sin(u16 angle) __asm__("func_800F3AE0");
extern void draw_filled_rectangle(Gfx **list, s32 left, s32 top, s32 right, s32 bottom, s32 red, s32 green, s32 blue,
                                  s32 alpha) __asm__("func_800F4DFC");
extern s32 select_audio_mode(u32 mode) __asm__("func_800AB95C");
extern void draw_paletted_image(Gfx **list, u8 *texels, s32 arg2, s32 arg3, s32 width, s32 height, s32 tileWidth,
                                s32 tileHeight, s32 x, s32 y, s32 width2, s32 height2, s32 s, s32 t,
                                f32 scaleX, f32 scaleY) __asm__("func_800F3D40");
extern void draw_ci4_image(Gfx **list, u8 *texels, u8 *palette, s32 width, s32 height, s32 tileWidth,
                           s32 tileHeight, s32 x, s32 y, s32 width2, s32 height2, s32 s, s32 t, f32 scaleX,
                           f32 scaleY) __asm__("func_800F41C0");
extern void begin_text_draw(Gfx **gfx) __asm__("func_8010698C");
extern void set_texture_draw_color(s32 red, s32 green, s32 blue, s32 alpha) __asm__("func_8010555C");
extern void select_texture_draw_entry(s32 index) __asm__("func_801054E0");
extern void set_texture_draw_position(s32 x, s32 y) __asm__("func_8010552C");
extern void draw_text_lines(Gfx **gfx, u8 *text, s32 lineCount, s32 lineHeight, s32 maxChars) __asm__("func_80105C68");

void draw_unit_select_screen(void) __asm__("func_800C5C60");

void draw_unit_select_screen(void)
{
    s32 x;
    s32 y;
    s32 mode;
    s32 col;
    s32 entry;
    s32 width;
    u8 *ci4;

    GFX_COMMAND(gFrontendDisplayList++, 0xE7000000U, 0);
    GFX_COMMAND(gFrontendDisplayList++, 0xBA001402U, 0);
    SET_COMBINE_SHADE();
    GFX_COMMAND(gFrontendDisplayList++, 0xB900031DU, 0x0F0A4000);
    GFX_COMMAND(gFrontendDisplayList++, 0xBA001301U, 0);
    GFX_COMMAND(gFrontendDisplayList++, 0xBA001001U, 0);
    GFX_COMMAND(gFrontendDisplayList++, 0xBA000C02U, 0);
    GFX_COMMAND(gFrontendDisplayList++, 0xBA000903U, 0xC00);
    GFX_COMMAND(gFrontendDisplayList++, 0xBA000E02U, 0x8000);
    SET_COMBINE_SHADE();
    GFX_COMMAND(gFrontendDisplayList++, 0xBA000E02U, 0x8000);
    LOAD_PALETTE(BUNDLE_ENTRY(28), 0x073FC000);
    for (y = 0; y < 4; y++) {
        for (col = 0; col < 6; col++) {
            draw_paletted_image(&gFrontendDisplayList, (u8 *)(BUNDLE_ENTRY(28) + 0x200), 2, 1, 0x40, 0x40, 0x20,
                                0x20, col << 6, y << 6, 0x40, 0x40, 0, 0, 1.0f, 1.0f);
        }
    }
    GFX_COMMAND(gFrontendDisplayList++, 0xB900031DU, 0x00504240);
    D_80327EEC += D_80327EF0;
    if (D_80327EEC > 0xFF) {
        D_80327EEC = 0xFF;
    }
    if (D_80327EEC < 0) {
        D_80327EEC = 0;
    }
    GFX_COMMAND(gFrontendDisplayList++, 0xBA000C02U, 0x2000);
    GFX_COMMAND(gFrontendDisplayList++, 0xFC119623U, 0xFF2FFFFFU);
    angle_sin(D_80133FE0 << 8);
    GFX_COMMAND(gFrontendDisplayList++, 0xFA000101U, D_80327EEF | 0xFFFFFF00U);
    mode = select_audio_mode(4);
    LOAD_PALETTE(BUNDLE_ENTRY(0), 0x073FC000);
    draw_paletted_image(&gFrontendDisplayList, (u8 *)(BUNDLE_ENTRY(0) + 0x200), 2, 1, 0x81, 0x48, 0x20, 0x20, 0x1E,
                        0x16, 0xA2, 0x5C, 0, 0, 0.8f, 0.8f);
    select_audio_mode(mode);
    GFX_COMMAND(gFrontendDisplayList++, 0xFA000101U, ((0xFF - D_80327EEC) & 0xFF) | 0xFFFFFF00U);
    LOAD_PALETTE(BUNDLE_ENTRY(0), 0x073FC000);
    draw_paletted_image(&gFrontendDisplayList, (u8 *)(BUNDLE_ENTRY(0) + 0x200), 2, 1, 0x81, 0x48, 0x20, 0x20, 0x1E,
                        0x16, 0xA2, 0x5C, 0, 0, 0.8f, 0.8f);
    mode = select_audio_mode(4);
    LOAD_PALETTE(BUNDLE_ENTRY(2), 0x0703C000);
    ci4 = (u8 *)BUNDLE_ENTRY(2);
    draw_ci4_image(&gFrontendDisplayList, ci4 + 0xA0, ci4, 0x82, 0x33, 0x20, 0x20, 0x1E, 0x20, 0xA2, 0x3F, 0, 0,
                   0.8f, 0.8f);
    D_80133FE0++;
    select_audio_mode(mode);
    entry = D_80134A28[D_80134010[D_80327EE8]];
    if (entry != 0) {
        DRAW_ENTRY_IMAGE(entry, 0x17, 0x17, 0xA4, 0x16, 0x1C, 0x1C, 0.8f);
    }
    entry = D_80134A50[D_80134010[D_80327EE8]];
    if (entry != 0) {
        DRAW_ENTRY_IMAGE(entry, 0x17, 0x17, 0x88, 0x16, 0x1C, 0x1C, 0.8f);
    }
    SET_COMBINE_SHADE();
    DRAW_IMAGE(11, 0xA9, 8, 0x17, 0xE, 1.0f);
    DRAW_IMAGE(12, 7, 0x57, 0x17, 0x16, 1.0f);
    DRAW_IMAGE(5, 0xA9, 7, 0x17, 0x6D, 1.0f);
    SET_COMBINE_SHADE();
    DRAW_IMAGE(13, 8, 0x57, 0xC0, 0x16, 1.0f);
    DRAW_IMAGE(14, 0x6A, 8, 0xC0, 0xE, 1.0f);
    DRAW_IMAGE(15, 7, 0x5E, 0x123, 0x16, 1.0f);
    DRAW_IMAGE(16, 0x63, 0x20, 0xC0, 0x54, 1.0f);
    LOAD_PALETTE(BUNDLE_ENTRY(25), 0x073FC000);
    draw_paletted_image(&gFrontendDisplayList, (u8 *)(BUNDLE_ENTRY(25) + 0x200), 2, 1, 0x1E, 8, 0x20, 0x20, 0x103,
                        0x1C, 0x1E, 8, 0, 0, 1.0f, 1.0f);
    draw_paletted_image(&gFrontendDisplayList, (u8 *)(BUNDLE_ENTRY(25) + 0x200), 2, 1, 0x1E, 8, 0x20, 0x20, 0x103,
                        0x2A, 0x1E, 8, 0, 0, 1.0f, 1.0f);
    draw_paletted_image(&gFrontendDisplayList, (u8 *)(BUNDLE_ENTRY(25) + 0x200), 2, 1, 0x1E, 8, 0x20, 0x20, 0x103,
                        0x38, 0x1E, 8, 0, 0, 1.0f, 1.0f);
    draw_paletted_image(&gFrontendDisplayList, (u8 *)(BUNDLE_ENTRY(25) + 0x200), 2, 1, 0x1E, 8, 0x20, 0x20, 0x103,
                        0x46, 0x1E, 8, 0, 0, 1.0f, 1.0f);
    DRAW_IMAGE(26, 0x37, 0x32, 0xCA, 0x1D, 1.0f);
    draw_filled_rectangle(&gFrontendDisplayList, 0x104, 0x1D, D_80134988[D_80134010[D_80327EE8]][0] * 28.0f, 6, 0xFF,
                          0, 0, 0xFF);
    draw_filled_rectangle(&gFrontendDisplayList, 0x104, 0x2B, D_80134988[D_80134010[D_80327EE8]][1] * 28.0f, 6, 0xFF,
                          0, 0, 0xFF);
    draw_filled_rectangle(&gFrontendDisplayList, 0x104, 0x39, D_80134988[D_80134010[D_80327EE8]][2] * 28.0f, 6, 0xFF,
                          0, 0, 0xFF);
    draw_filled_rectangle(&gFrontendDisplayList, 0x104, 0x47, D_80134988[D_80134010[D_80327EE8]][3] * 28.0f, 6, 0xFF,
                          0, 0, 0xFF);
    SET_COMBINE_SHADE();
    DRAW_IMAGE(8, 0x58, 0x26, 0xD2, 0x74, 1.0f);
    DRAW_IMAGE(9, 7, 0x26, 0x123, 0x74, 1.0f);
    DRAW_IMAGE(6, 7, 0x1F, 0x17, 0x74, 1.0f);
    x = D_80134030[D_80134010[D_80327EE8]];
    GFX_COMMAND(gFrontendDisplayList++, 0xB900031DU, 0x00504240);
    width = 0xAC - x;
    width /= 2;
    mode = select_audio_mode(4);
    DRAW_IMAGE(5, x, 0x15, width + 0x21, 0x79, 1.0f);
    select_audio_mode(mode);
    GFX_COMMAND(gFrontendDisplayList++, 0xBA000E02U, 0x8000);
    SET_COMBINE_SHADE();
    DRAW_IMAGE(2, 7, 0x3F, 0x17, 0x9A, 1.0f);
    DRAW_IMAGE(3, 0x113, 8, 0x1C, 0xD9, 1.0f);
    DRAW_IMAGE(4, 7, 0x3F, 0x123, 0x9A, 1.0f);
    DRAW_IMAGE(7, 0xBB, 7, 0x17, 0x93, 1.0f);
    begin_text_draw(&gFrontendDisplayList);
    select_texture_draw_entry(1);
    set_texture_draw_color(0xFF, 0xBF, 0x17, 0xFF);
    set_texture_draw_position(0x23, 0xA0);
    draw_text_lines(&gFrontendDisplayList, D_80134960[D_80134010[D_80327EE8]], 5, 0xA, 0);
    SET_COMBINE_SHADE();
    GFX_COMMAND(gFrontendDisplayList++, 0xBA000E02U, 0x8000);
    GFX_COMMAND(gFrontendDisplayList++, 0xB900031DU, 0x00504240);
    mode = select_audio_mode(4);
    DRAW_IMAGE(1, 0x37, 0x37, 0xDA, 0x5D, 1.0f);
    select_audio_mode(mode);
}
