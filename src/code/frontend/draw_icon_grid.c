#include "types.h"

typedef struct GfxCommand {
    u32 w0;
    u32 w1;
} GfxCommand;

#define GFX_COORD(value) (((value) * 4) & 0xFFF)
#define GFX_WORDS(pkt, a, b) \
    {                         \
        GfxCommand *_g = (pkt); \
        _g->w0 = (a);         \
        _g->w1 = (b);         \
    }

extern GfxCommand *gMenuDisplayList __asm__("D_8037A174");
typedef struct IconTextures {
    u8 palette[0x20];
    u8 pixels[0x34];
    s32 frame;
} IconTextures;

extern IconTextures gIconTextures __asm__("D_8037AD78");

void draw_icon_grid(s32 count) __asm__("func_800D1BA0");

void draw_icon_grid(s32 count)
{
    s32 i;

    if (count == 0) {
        return;
    }
    GFX_WORDS(gMenuDisplayList++, 0xFC119623, 0xFF2FFFFF);
    GFX_WORDS(gMenuDisplayList++, 0xBA000E02, 0x8000);
    GFX_WORDS(gMenuDisplayList++, 0xB900031D, 0x504240);
    GFX_WORDS(gMenuDisplayList++, 0xFA000101, 0xFFFFFFFF);
    GFX_WORDS(gMenuDisplayList++, 0xFD500000, (u32)&gIconTextures.pixels[gIconTextures.frame]);
    GFX_WORDS(gMenuDisplayList++, 0xF5500000, 0x07000200);
    GFX_WORDS(gMenuDisplayList++, 0xE6000000, 0);
    GFX_WORDS(gMenuDisplayList++, 0xF3000000, 0x071FF200);
    GFX_WORDS(gMenuDisplayList++, 0xE7000000, 0);
    GFX_WORDS(gMenuDisplayList++, 0xF5400800, 0x200);
    GFX_WORDS(gMenuDisplayList++, 0xF2000000, 0x000FC07C);
    GFX_WORDS(gMenuDisplayList++, 0xFD100000, (u32)&gIconTextures.palette[gIconTextures.frame]);
    GFX_WORDS(gMenuDisplayList++, 0xE8000000, 0);
    GFX_WORDS(gMenuDisplayList++, 0xF5000100, 0x07000000);
    GFX_WORDS(gMenuDisplayList++, 0xE6000000, 0);
    GFX_WORDS(gMenuDisplayList++, 0xF0000000, 0x0703C000);
    GFX_WORDS(gMenuDisplayList++, 0xE7000000, 0);
    for (i = 0; i < count; i++) {
        s32 col = i % 3;
        s32 row = i / 3;
        s32 x = col * 75 + 0x2E + row * 3;
        s32 y = row * 2 + 0x78;

        GFX_WORDS(gMenuDisplayList++, 0xE4000000 | (GFX_COORD(x + 0x32) << 12) | GFX_COORD(row * 2 + 0x89), (GFX_COORD(x) << 12) | GFX_COORD(y));
        GFX_WORDS(gMenuDisplayList++, 0xB4000000, 0);
        GFX_WORDS(gMenuDisplayList++, 0xB3000000, 0x04000400);
    }
}
