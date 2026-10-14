#include "types.h"

extern void draw_text_char(void *context, u8 ch) __asm__("func_80106010");

void draw_text_string(void *context, u8 *text) __asm__("func_80105584");

void draw_text_string(void *context, u8 *text)
{
    u8 ch;

    while ((ch = *text++) != 0) {
        draw_text_char(context, ch);
    }
}
