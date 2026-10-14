#include "types.h"

typedef struct GfxCommand {
    u32 w0;
    u32 w1;
} GfxCommand;

typedef struct OverlayFrame {
    GfxCommand *main;
    GfxCommand *overlay;
} OverlayFrame;

#define GFX_SET_PRIM_COLOR_WORD 0xFA000101
#define GFX_TEXRECT_WORD 0xE4000000
#define GFX_RDPHALF_1_WORD 0xB4000000
#define GFX_RDPHALF_2_WORD 0xB3000000
#define GFX_TEXRECT_STEP 0x04000400
#define GFX_COORD(value) (((value) * 4) & 0xFFF)

extern OverlayFrame *get_render_frame_record_alt(void) __asm__("func_8007F060");

void draw_overlay_filled_rect(s16 x, s16 y, s16 width, s16 height, u8 red, u8 green, u8 blue, u8 alpha)
    __asm__("func_800AB3C4");

void draw_overlay_filled_rect(s16 x, s16 y, s16 width, s16 height, u8 red, u8 green, u8 blue, u8 alpha)
{
    OverlayFrame *frame;
    GfxCommand *command;

    frame = get_render_frame_record_alt();
    command = frame->overlay++;
    command->w0 = GFX_SET_PRIM_COLOR_WORD;
    command->w1 = (red << 24) | (green << 16) | (blue << 8) | alpha;
    command = frame->overlay++;
    command->w0 = GFX_TEXRECT_WORD | (GFX_COORD(x + width) << 12) | GFX_COORD(y + height);
    command->w1 = (GFX_COORD(x) << 12) | GFX_COORD(y);
    command = frame->overlay++;
    command->w0 = GFX_RDPHALF_1_WORD;
    command->w1 = 0;
    command = frame->overlay++;
    command->w0 = GFX_RDPHALF_2_WORD;
    command->w1 = GFX_TEXRECT_STEP;
}
