#include "types.h"

typedef struct TextGlyph {
    u8 pad0[0x2];
    u8 width;
    u8 pad3;
} TextGlyph;

typedef struct TextFont {
    u8 pad00[0x18];
    u8 glyphIndex[0x80];
    TextGlyph glyphs[1];
} TextFont;

extern void draw_text_char(void *context, s32 ch) __asm__("func_80106010");
extern s32 gTextureDrawX __asm__("D_803AAD88");
extern f32 gTextureDrawScaleX __asm__("D_803AAD90");
extern TextFont *gTextureDrawEntryData __asm__("D_803AAD98");
extern s32 gTextDrawSpacing __asm__("D_803B75A0");

void draw_centered_text_integer(void *context, s32 unused, s64 value) __asm__("func_801057DC");

void draw_centered_text_integer(void *context, s32 unused, s64 value) {
    s64 rest;
    s32 width;
    s32 glyph;
    s32 ch;

    width = 0;
    rest = value;

    do {
        ch = rest % 10;
        glyph = gTextureDrawEntryData->glyphIndex[ch + '0'];
        if (glyph != -1) {
            width += (s32)(gTextureDrawEntryData->glyphs[glyph].width * gTextureDrawScaleX);
        }
        rest /= 10;
    } while (rest != 0);
    gTextureDrawX += width / 2;
    if (value < 0) {
        value = -value;
    }
    gTextDrawSpacing = -1;
    do {
        draw_text_char(context, value % 10 + '0');
        value /= 10;
    } while (value != 0);
    gTextDrawSpacing = 1;
}
