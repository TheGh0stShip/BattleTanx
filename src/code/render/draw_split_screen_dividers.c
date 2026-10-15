#include "types.h"

typedef struct GfxCommand {
    u32 w0;
    u32 w1;
} GfxCommand;

extern void draw_overlay_filled_rect(s16 x, s16 y, s16 width, s16 height, u8 red, u8 green, u8 blue, u8 alpha)
    __asm__("func_800AB3C4");
extern void draw_filled_box(GfxCommand **gfx, s32 x, s32 y, s32 width, s32 height, s32 red, s32 green, s32 blue,
                            s32 alpha) __asm__("func_800F4DFC");
extern GfxCommand *gTextDisplayList __asm__("D_8037A174");
extern s32 gPlayerCount __asm__("D_8037A140");
extern s32 D_8012578C;

void draw_split_screen_dividers(void) __asm__("func_800F66F0");

void draw_split_screen_dividers(void)
{
    if (D_8012578C == 4) {
        switch (gPlayerCount) {
        case 2:
            draw_overlay_filled_rect(0, 0x77, 0x140, 2, 0, 0, 0, 0xFF);
            break;
        case 3:
            draw_overlay_filled_rect(0, 0x77, 0x140, 2, 0, 0, 0, 0xFF);
            draw_overlay_filled_rect(0x9F, 0x78, 2, 0x78, 0, 0, 0, 0xFF);
            break;
        case 4:
            draw_overlay_filled_rect(0, 0x77, 0x140, 2, 0, 0, 0, 0xFF);
            draw_overlay_filled_rect(0x9F, 0, 2, 0xF0, 0, 0, 0, 0xFF);
            break;
        }
    } else {
        switch (gPlayerCount) {
        case 2:
            draw_filled_box(&gTextDisplayList, 0, 0x77, 0x140, 2, 0, 0, 0, 0xFF);
            break;
        case 3:
            draw_filled_box(&gTextDisplayList, 0, 0x77, 0x140, 2, 0, 0, 0, 0xFF);
            draw_filled_box(&gTextDisplayList, 0x9F, 0x78, 2, 0x78, 0, 0, 0, 0xFF);
            break;
        case 4:
            draw_filled_box(&gTextDisplayList, 0, 0x77, 0x140, 2, 0, 0, 0, 0xFF);
            draw_filled_box(&gTextDisplayList, 0x9F, 0, 2, 0xF0, 0, 0, 0, 0xFF);
            break;
        }
    }
}
