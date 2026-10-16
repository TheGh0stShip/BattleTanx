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
typedef struct FrameSheet {
    s32 count;
    s32 offsets[15];
    u8 pad40[0x1C0];
    u8 texels[1];
} FrameSheet;
extern FrameSheet gFrame __asm__("D_80382D80");
extern u8 gFrameTexels[] __asm__("D_80382F80");

/* "BATTLE STATS": the same literal emitted with draw_stats_frame (shared within the translation unit). */
extern char D_800750BC[];

extern void draw_paletted_image(Gfx **list, u8 *texels, s32 arg2, s32 arg3, s32 width, s32 height, s32 tileWidth,
                                s32 tileHeight, s32 x, s32 y, s32 width2, s32 height2, s32 s, s32 t,
                                f32 scaleX, f32 scaleY) __asm__("func_800F3D40");
extern void draw_fill_box(Gfx **list, s32 x, s32 y, s32 w, s32 h, s32 r, s32 g, s32 b, s32 a) __asm__("func_800F4DFC");
extern void begin_text_draw(Gfx **gfx) __asm__("func_8010698C");
extern void select_texture_draw_entry(s32 index) __asm__("func_801054E0");
extern void set_texture_draw_position(s32 x, s32 y) __asm__("func_8010552C");
extern void draw_text_centered(Gfx **gfx, char *text, s32 left, s32 right) __asm__("func_80105A50");

#define LOAD_FRAME_TEX(idx) \
    GFX_COMMAND(gDisplayList++, 0xFD100000U, (u32)((u8 *)&gFrame + gFrame.offsets[idx])); \
    GFX_COMMAND(gDisplayList++, 0xE8000000U, 0); \
    GFX_COMMAND(gDisplayList++, 0xF5000100U, 0x07000000); \
    GFX_COMMAND(gDisplayList++, 0xE6000000U, 0); \
    GFX_COMMAND(gDisplayList++, 0xF0000000U, 0x073FC000); \
    GFX_COMMAND(gDisplayList++, 0xE7000000U, 0);

void draw_player_stats_panel(s32 x, s32 y) __asm__("func_80102A30");

void draw_player_stats_panel(s32 x, s32 y) {
    draw_fill_box(&gDisplayList, x, y, 0x86, 0x64, 0, 0, 0, 0x80);
    begin_text_draw(&gDisplayList);
    select_texture_draw_entry(4);
    set_texture_draw_position(0, y + 5);
    draw_text_centered(&gDisplayList, D_800750BC, x, x + 0x86);
    GFX_COMMAND(gDisplayList++, 0xFCFFFFFFU, 0xFFFCF279U);
    GFX_COMMAND(gDisplayList++, 0xBA000E02U, 0x8000);
    LOAD_FRAME_TEX(10);
    draw_paletted_image(&gDisplayList, &gFrameTexels[gFrame.offsets[10]], 2, 1, 0x86, 4, 0x20, 0x20,
                        x, y, 0x86, 4, 0, 0, 1.0f, 1.0f);
    LOAD_FRAME_TEX(8);
    draw_paletted_image(&gDisplayList, &gFrameTexels[gFrame.offsets[8]], 2, 1, 4, 0x5C, 0x20, 0x20,
                        x, y + 4, 4, 0x5C, 0, 0, 1.0f, 1.0f);
    LOAD_FRAME_TEX(9);
    draw_paletted_image(&gDisplayList, &gFrameTexels[gFrame.offsets[9]], 2, 1, 4, 0x5C, 0x20, 0x20,
                        x + 0x82, y + 4, 4, 0x5C, 0, 0, 1.0f, 1.0f);
    LOAD_FRAME_TEX(7);
    draw_paletted_image(&gDisplayList, &gFrameTexels[gFrame.offsets[7]], 2, 1, 0x86, 4, 0x20, 0x20,
                        x, y + 0x60, 0x86, 4, 0, 0, 1.0f, 1.0f);
}
