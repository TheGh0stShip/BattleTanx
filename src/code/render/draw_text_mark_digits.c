#include "types.h"

extern u8 gTextDigitFlag __asm__("D_803B75A9");

extern void draw_text_char(void **displayList, u8 ch) __asm__("func_8010647C");

void draw_text_mark_digits(void **displayList, u8 *text) __asm__("func_80105750");

void draw_text_mark_digits(void **displayList, u8 *text) {
    u8 ch;

    while ((ch = *text++) != 0) {
        if ((u32)(ch - '0') < 10) {
            gTextDigitFlag = 1;
        } else {
            gTextDigitFlag = 0;
        }
        draw_text_char(displayList, ch);
    }
    gTextDigitFlag = 0;
}
