#include "types.h"

extern s32 D_803B75A0;
extern u8 gTextDigitFlag __asm__("D_803B75A9");

extern void draw_text_char(void **displayList, u8 ch) __asm__("func_8010647C");

void draw_text_integer(void **displayList, s64 value) __asm__("func_80105688");

/* Emits the decimal digits of |value|, least significant first. */
void draw_text_integer(void **displayList, s64 value) {
    if (value < 0) {
        value = -value;
    }
    D_803B75A0 = -1;
    gTextDigitFlag = 1;
    do {
        u8 ch = value % 10 + '0';
        draw_text_char(displayList, ch);
        value /= 10;
    } while (value != 0);
    D_803B75A0 = 1;
    gTextDigitFlag = 0;
}
