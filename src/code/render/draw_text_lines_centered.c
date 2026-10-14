#include "types.h"

extern void draw_text_char(void *context, u8 ch) __asm__("func_80106010");
extern s32 gTextureDrawX __asm__("D_803AAD88");
extern s32 gTextureDrawY __asm__("D_803AAD8C");
extern f32 gTextScale __asm__("D_803AAD90");
extern u8 *gTextureDrawEntryData __asm__("D_803AAD98");
extern s32 gTextSpaceWidth __asm__("D_803B75A0");

void draw_text_lines_centered(void *context, u8 *text, s32 lineCount, s32 lineHeight, s32 left, s32 right) __asm__("func_80105D90");

void draw_text_lines_centered(void *context, u8 *text, s32 lineCount, s32 lineHeight, s32 left, s32 right)
{
    s32 line;
    s32 width;
    s32 len;
    s32 span;
    u8 *p;
    s32 c;
    u8 *q;

    for (line = 0; line < lineCount; line++) {
        span = right - left;
        q = text;
        width = 0;
        p = text;
        for (;;) {
            c = *p++;
            if (c == '\n') {
                goto measured;
            }
            if (c == ' ') {
                width += (s32)((gTextSpaceWidth * 3) * gTextScale);
            } else {
                c = *(gTextureDrawEntryData + c + 0x18);
                if (c == 0xFF) {
                    continue;
                }
                width += (s32)(*(gTextureDrawEntryData + (c << 2) + 0x9A) * gTextScale);
            }
        }
    measured:
        gTextureDrawX = (span - width) / 2 + left;
        c = *q;
        len = 0;
        q++;
        while (c != '\n') {
            draw_text_char(context, c);
            c = *q;
            len++;
            q++;
        }
        text += len + 1;
        gTextureDrawY += lineHeight;
    }
}
