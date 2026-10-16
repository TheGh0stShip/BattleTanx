#include "types.h"

typedef struct GfxCommand {
    u32 w0;
    u32 w1;
} GfxCommand;

typedef struct TextGlyph {
    u8 x;
    u8 y;
    u8 width;
    u8 pad3;
} TextGlyph;

typedef struct TextFont {
    s32 pad00;
    s32 height;
    s32 pad08;
    s32 imageWidth;
    s32 pad10;
    s32 imageOffset;
    u8 glyphIndex[0x80];
    TextGlyph glyphs[1];
} TextFont;

#define GFX_WORDS(pkt, a, b)    \
    {                           \
        GfxCommand *_g = (pkt); \
        _g->w0 = (a);           \
        _g->w1 = (b);           \
    }

extern s32 gTextureDrawX __asm__("D_803AAD88");
extern s32 gTextureDrawY __asm__("D_803AAD8C");
extern f32 gTextureDrawScaleX __asm__("D_803AAD90");
extern f32 gTextureDrawScaleY __asm__("D_803AAD94");
extern TextFont *gTextureDrawEntryData __asm__("D_803AAD98");
extern s32 gTextDrawSpacing __asm__("D_803B75A0");
extern u8 gTextureDrawRed __asm__("D_803B75A4");
extern u8 gTextureDrawGreen __asm__("D_803B75A5");
extern u8 gTextureDrawBlue __asm__("D_803B75A6");
extern u8 gTextureDrawAlpha __asm__("D_803B75A7");
extern u8 gTextDrawCharCount __asm__("D_803B75A8");
extern u8 gTextureDrawOption __asm__("D_803B75A9");
extern s32 gTextureDrawMode __asm__("D_803B75AC");

void draw_text_char_fixed(GfxCommand **context, u32 ch) __asm__("func_8010647C");

void draw_text_char_fixed(GfxCommand **context, u32 ch)
{
    GfxCommand *gdl;
    GfxCommand unused;
    s32 height;
    s32 x;
    s32 y;
    s32 width;
    s32 sw;
    s32 sh;
    u32 lrs;
    u32 lrt;

    gTextDrawCharCount++;
    if (ch == ' ') {
        gTextureDrawX += (s32)((gTextDrawSpacing * 3) * gTextureDrawScaleX);
        return;
    }
    ch = gTextureDrawEntryData->glyphIndex[ch];
    if (ch == 0xFF) {
        return;
    }
    gdl = *context;
    height = gTextureDrawEntryData->height;
    x = gTextureDrawEntryData->glyphs[ch].x;
    y = gTextureDrawEntryData->glyphs[ch].y;
    width = gTextureDrawEntryData->glyphs[ch].width;
    if (gTextDrawSpacing == -1) {
        if (gTextureDrawOption) gTextureDrawX += (s32)(-gTextureDrawMode * gTextureDrawScaleX); else gTextureDrawX += (s32)(-width * gTextureDrawScaleX);
    }
    sw = (s32)(width * gTextureDrawScaleX);
    lrt = (((y + height) << 2) & 0xFFF);
    lrs = (((x + width) << 2) << 12);
    GFX_WORDS(gdl++, 0xFA000000,
              (gTextureDrawRed << 24) | (gTextureDrawGreen << 16) | (gTextureDrawBlue << 8) |
                  gTextureDrawAlpha);
    {
        u32 image = (u32)gTextureDrawEntryData + gTextureDrawEntryData->imageOffset;

        GFX_WORDS(gdl++, 0xFD680000 | ((gTextureDrawEntryData->imageWidth - 1) & 0xFFF), image);
    }
    GFX_WORDS(gdl++, 0xF5680000 | (((u32)(width + 8) >> 3) << 9), 0x07080200);
    GFX_WORDS(gdl++, 0xE6000000, 0);
    GFX_WORDS(gdl++, 0xF4000000 | ((x << 2) << 12) | (y << 2),
              0x07000000 | lrs | lrt);
    GFX_WORDS(gdl++, 0xE7000000, 0);
    GFX_WORDS(gdl++, 0xF5680000 | (((u32)(width + 8) >> 3) << 9), 0x00080200);
    GFX_WORDS(gdl++, 0xF2000000 | ((x << 2) << 12) | (y << 2),
              lrs | lrt);
    {
        GfxCommand *_g = gdl++;
        s32 dy = gTextureDrawY;
        f32 sy = gTextureDrawScaleY;
        u32 w0;
        u32 uy;

        uy = (dy << 2) & 0xFFF;
        _g->w1 = (((gTextureDrawX << 2) & 0xFFF) << 12) | ((dy << 2) & 0xFFF);
        w0 = (((gTextureDrawX + sw) << 2) & 0xFFF) << 12;
        sw = (s32)(height * sy);
        _g->w0 = 0xE4000000 | w0 | (((dy + sw) << 2) & 0xFFF);
    }
    GFX_WORDS(gdl++, 0xB4000000,
              ((u32)(x * 32.0) << 16) | ((u32)(y * 32.0) & 0xFFFF));
    GFX_WORDS(gdl++, 0xB3000000,
              ((u32)(1024.0f / gTextureDrawScaleX) << 16) |
                  ((u32)(1024.0f / gTextureDrawScaleY) & 0xFFFF));
    if (gTextDrawSpacing == 1) {
        if (gTextureDrawOption) gTextureDrawX += (s32)(gTextureDrawMode * gTextureDrawScaleX);
        else gTextureDrawX += (s32)(width * gTextureDrawScaleX);
    }
    *context = gdl;
}
