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

extern Gfx *gDisplayList __asm__("D_8037A174");
extern u8 gFramePalettes[] __asm__("D_80382D80");
extern s32 gFrameImageOffsets[] __asm__("D_80382D84");
extern u8 gFrameTexels[] __asm__("D_80382F80");

extern void draw_paletted_image(Gfx **list, u8 *texels, s32 arg2, s32 arg3, s32 width, s32 height, s32 tileWidth,
                                s32 tileHeight, s32 x, s32 y, s32 width2, s32 height2, s32 s, s32 t,
                                f32 scaleX, f32 scaleY) __asm__("func_800F3D40");
extern void draw_fill_box(Gfx **list, s32 x, s32 y, s32 w, s32 h, s32 r, s32 g, s32 b, s32 a) __asm__("func_800F4DFC");
extern void begin_text_draw(Gfx **gfx) __asm__("func_8010698C");
extern void select_texture_draw_entry(s32 index) __asm__("func_801054E0");
extern void set_texture_draw_position(s32 x, s32 y) __asm__("func_8010552C");
extern void draw_text_centered(Gfx **gfx, char *text, s32 left, s32 right) __asm__("func_80105A50");

#define LOAD_FRAME_TEX(idx) \
    GFX_COMMAND(gDisplayList++, 0xFD100000U, (u32)&gFramePalettes[gFrameImageOffsets[idx]]); \
    GFX_COMMAND(gDisplayList++, 0xE8000000U, 0); \
    GFX_COMMAND(gDisplayList++, 0xF5000100U, 0x07000000); \
    GFX_COMMAND(gDisplayList++, 0xE6000000U, 0); \
    GFX_COMMAND(gDisplayList++, 0xF0000000U, 0x073FC000); \
    GFX_COMMAND(gDisplayList++, 0xE7000000U, 0);

void draw_stats_frame(s32 x, s32 y, s32 showTitle, s32 tall) __asm__("func_80102050");

void draw_stats_frame(s32 x, s32 y, s32 showTitle, s32 tall) {
    draw_fill_box(&gDisplayList, x, y, 0x108, tall ? 0x96 : 0x5F, 0, 0, 0, 0x80);
    begin_text_draw(&gDisplayList);
    select_texture_draw_entry(2);
    set_texture_draw_position(0, y + 5);
    if (showTitle) {
        draw_text_centered(&gDisplayList, "BATTLE STATS", 0, 0x140);
    }
    select_texture_draw_entry(4);
    GFX_COMMAND(gDisplayList++, 0xFCFFFFFFU, 0xFFFCF279U);
    GFX_COMMAND(gDisplayList++, 0xBA000E02U, 0x8000);
    if (tall) {
        LOAD_FRAME_TEX(5);
        draw_paletted_image(&gDisplayList, &gFrameTexels[gFrameImageOffsets[5]], 2, 1, 0x108, 4, 0x20, 0x20,
                            x, y, 0x108, 4, 0, 0, 1.0f, 1.0f);
        LOAD_FRAME_TEX(1);
        draw_paletted_image(&gDisplayList, &gFrameTexels[gFrameImageOffsets[1]], 2, 1, 4, 0x96, 0x20, 0x20,
                            x, y + 4, 4, 0x96, 0, 0, 1.0f, 1.0f);
        LOAD_FRAME_TEX(3);
        draw_paletted_image(&gDisplayList, &gFrameTexels[gFrameImageOffsets[3]], 2, 1, 4, 0x96, 0x20, 0x20,
                            x + 0x104, y + 4, 4, 0x96, 0, 0, 1.0f, 1.0f);
        LOAD_FRAME_TEX(5);
        draw_paletted_image(&gDisplayList, &gFrameTexels[gFrameImageOffsets[5]], 2, 1, 0x108, 4, 0x20, 0x20,
                            x, y + 0x96, 0x108, 4, 0, 0, 1.0f, 1.0f);
    } else {
        LOAD_FRAME_TEX(5);
        draw_paletted_image(&gDisplayList, &gFrameTexels[gFrameImageOffsets[5]], 2, 1, 0x108, 4, 0x20, 0x20,
                            x, y, 0x108, 4, 0, 0, 1.0f, 1.0f);
        LOAD_FRAME_TEX(2);
        draw_paletted_image(&gDisplayList, &gFrameTexels[gFrameImageOffsets[2]], 2, 1, 4, 0x57, 0x20, 0x20,
                            x, y + 4, 4, 0x57, 0, 0, 1.0f, 1.0f);
        LOAD_FRAME_TEX(4);
        draw_paletted_image(&gDisplayList, &gFrameTexels[gFrameImageOffsets[4]], 2, 1, 4, 0x57, 0x20, 0x20,
                            x + 0x104, y + 4, 4, 0x57, 0, 0, 1.0f, 1.0f);
        LOAD_FRAME_TEX(5);
        draw_paletted_image(&gDisplayList, &gFrameTexels[gFrameImageOffsets[5]], 2, 1, 0x108, 4, 0x20, 0x20,
                            x, y + 0x5B, 0x108, 4, 0, 0, 1.0f, 1.0f);
    }
}
