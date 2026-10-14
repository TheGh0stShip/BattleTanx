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

extern void draw_text_char(void *context, u8 ch) __asm__("func_80106010");
extern s32 gTextureDrawX __asm__("D_803AAD88");
extern f32 gTextureDrawScaleX __asm__("D_803AAD90");
extern TextFont *gTextureDrawEntryData __asm__("D_803AAD98");
extern s32 gTextDrawSpacing __asm__("D_803B75A0");

s32 draw_centered_text_line(void *context, u8 *text, s32 left, s32 right) __asm__("func_80105B48");

s32 draw_centered_text_line(void *context, u8 *text, s32 left, s32 right)
{
    s32 width = 0;
    s32 len;
    u8 *p = text;
    u32 c;

    right -= left;
    while (1) {
        c = *p++;
        if (c == '\n') {
            break;
        }
        if (c == ' ') {
            width += (s32)((gTextDrawSpacing * 3) * gTextureDrawScaleX);
        } else {
            c = gTextureDrawEntryData->glyphIndex[c];
            if (c != 0xFF) {
                width += (s32)(gTextureDrawEntryData->glyphs[c].width * gTextureDrawScaleX);
            }
        }
    }
    len = 0;
    gTextureDrawX = (right - width) / 2 + left;
    c = *text++;
    while (c != '\n') {
        draw_text_char(context, c);
        len++;
        c = *text++;
    }
    return len + 1;
}
