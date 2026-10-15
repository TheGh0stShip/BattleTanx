#include "types.h"

typedef struct GfxCommand {
    u32 w0;
    u32 w1;
} GfxCommand;

typedef struct BarTextures {
    u8 palette[0x14];
    s32 frame;
    u8 pad18[0x8];
    u8 pixels[1];
} BarTextures;

#define GFX_COORD(value) (((value) * 4) & 0xFFF)
#define GFX_WORDS(pkt, a, b)    \
    {                           \
        GfxCommand *_g = (pkt); \
        _g->w0 = (a);           \
        _g->w1 = (b);           \
    }

extern GfxCommand *gMenuDisplayList __asm__("D_8037A174");
extern u8 gMenuAlpha __asm__("D_8037A170");
extern BarTextures gBarTextures __asm__("D_8037AD78");

void draw_short_segment_bar(s32 x, s32 y, s32 value, s32 max) __asm__("func_800FFB58");

void draw_short_segment_bar(s32 x, s32 y, s32 value, s32 max)
{
    s32 filled;
    s32 i;

    GFX_WORDS(gMenuDisplayList++, 0xFD500000, (u32)&gBarTextures.pixels[gBarTextures.frame]);
    GFX_WORDS(gMenuDisplayList++, 0xF5500000, 0x07000200);
    GFX_WORDS(gMenuDisplayList++, 0xE6000000, 0);
    GFX_WORDS(gMenuDisplayList++, 0xF3000000, 0x070FF400);
    GFX_WORDS(gMenuDisplayList++, 0xE7000000, 0);
    GFX_WORDS(gMenuDisplayList++, 0xF5400400, 0x200);
    GFX_WORDS(gMenuDisplayList++, 0xF2000000, 0x0007C07C);
    GFX_WORDS(gMenuDisplayList++, 0xFA000101, 0xC8320000 | gMenuAlpha);
    GFX_WORDS(gMenuDisplayList++, 0xFD100000, (u32)&gBarTextures.palette[gBarTextures.frame]);
    GFX_WORDS(gMenuDisplayList++, 0xE8000000, 0);
    GFX_WORDS(gMenuDisplayList++, 0xF5000100, 0x07000000);
    GFX_WORDS(gMenuDisplayList++, 0xE6000000, 0);
    GFX_WORDS(gMenuDisplayList++, 0xF0000000, 0x0703C000);
    GFX_WORDS(gMenuDisplayList++, 0xE7000000, 0);
    GFX_WORDS(gMenuDisplayList++, 0xFC119623, 0xFF2FFFFF);
    GFX_WORDS(gMenuDisplayList++, 0xBA000E02, 0x8000);
    GFX_WORDS(gMenuDisplayList++, 0xB900031D, 0x0F0A4000);
    filled = (f32)value / (f32)max * 10.0f;
    for (i = 0; i < filled; i++) {
        GFX_WORDS(gMenuDisplayList++, 0xE4000000 | (GFX_COORD(x + 5) << 12) | GFX_COORD(y + 5),
                  (GFX_COORD(x) << 12) | GFX_COORD(y));
        x += 5;
        GFX_WORDS(gMenuDisplayList++, 0xB4000000, 0);
        GFX_WORDS(gMenuDisplayList++, 0xB3000000, 0x04000400);
    }
    GFX_WORDS(gMenuDisplayList++, 0xFA000101, 0x20202000 | gMenuAlpha);
    for (i = 0; i < 10 - filled; i++) {
        GFX_WORDS(gMenuDisplayList++, 0xE4000000 | (GFX_COORD(x + 5) << 12) | GFX_COORD(y + 5),
                  (GFX_COORD(x) << 12) | GFX_COORD(y));
        x += 5;
        GFX_WORDS(gMenuDisplayList++, 0xB4000000, 0);
        GFX_WORDS(gMenuDisplayList++, 0xB3000000, 0x04000400);
    }
}
