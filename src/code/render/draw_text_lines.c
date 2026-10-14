#include "types.h"

extern void draw_text_char(void *context, u8 ch) __asm__("func_80106010");
extern s32 gTextureDrawX __asm__("D_803AAD88");
extern s32 gTextureDrawY __asm__("D_803AAD8C");
extern u8 gTextDrawnCharCount __asm__("D_803B75A8");

void draw_text_lines(void *context, u8 *text, s32 lineCount, s32 lineHeight, s32 maxChars) __asm__("func_80105C68");

void draw_text_lines(void *context, u8 *text, s32 lineCount, s32 lineHeight, s32 maxChars)
{
    s32 startX = gTextureDrawX;
    s32 line;
    s32 len;
    s32 step;
    u8 c;
    u8 *p;

    gTextDrawnCharCount = 0;
    for (line = 0; line < lineCount; line++) {
        if (maxChars != 0 && gTextDrawnCharCount >= maxChars) {
            return;
        }
        c = *text;
        len = 0;
        p = text + 1;
        while (c != '\n') {
            if (maxChars != 0 && gTextDrawnCharCount >= maxChars) {
                step = len;
                goto next_line;
            }
            draw_text_char(context, c);
            c = *p;
            len++;
            p++;
        }
        step = len + 1;
next_line:
        gTextureDrawX = startX;
        gTextureDrawY += lineHeight;
        text += step;
    }
}
