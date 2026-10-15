#include "types.h"

typedef struct GfxCommand {
    u32 w0;
    u32 w1;
} GfxCommand;

void draw_filled_rectangle() __asm__("func_800F4DFC");

void draw_filled_rectangle(head, x, y, width, height, red, green, blue, alpha)
    GfxCommand **head;
    s32 x, y, width, height;
    s32 red, green, blue, alpha;
{
    GfxCommand *gfx;
    GfxCommand *cmd0;
    GfxCommand *cmd1;
    GfxCommand *cmd2;
    GfxCommand *cmd3;
    register GfxCommand *cmd4 __asm__("$17");
    register GfxCommand *cmd5 __asm__("$18");
    register GfxCommand *cmd6 __asm__("$19");
    volatile s32 *colors;

    colors = &red;
    gfx = *head;
    cmd0 = gfx++;
    cmd1 = gfx++;
    cmd2 = gfx++;
    cmd3 = gfx++;
    cmd4 = gfx++;
    cmd5 = gfx++;
    cmd6 = gfx++;
    cmd0->w0 = 0xE7000000;
    cmd0->w1 = 0;
    cmd1->w0 = 0xFCFFFFFF;
    cmd1->w1 = 0xFFFDF6FB;
    cmd2->w0 = 0xB900031D;
    cmd2->w1 = 0x00504240;
    cmd3->w0 = 0xFA000101;
    cmd3->w1 = (colors[0] << 24) | ((colors[1] & 0xFF) << 16) |
               ((colors[2] & 0xFF) << 8) | (colors[3] & 0xFF);
    cmd4->w0 = ((((x + width) * 4) & 0xFFF) << 12) |
                ((((y + height) * 4) & 0xFFF) | 0xE4000000);
    cmd4->w1 = (((x * 4) & 0xFFF) << 12) | ((y * 4) & 0xFFF);
    cmd5->w0 = 0xB4000000;
    cmd5->w1 = 0;
    cmd6->w0 = 0xB3000000;
    cmd6->w1 = 0x04000400;
    *head = gfx;
}
