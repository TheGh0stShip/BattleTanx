#include "types.h"

extern s32 D_803B75A0;
extern void draw_text_char(void *context, u8 ch) __asm__("func_80106010");

void draw_reversed_decimal_digits(void *context, s32 unused, s64 value) __asm__("func_801055D4");

void draw_reversed_decimal_digits(void *context, s32 unused, s64 value) {
    u8 digit;

    if (value < 0) {
        value = -value;
    }
    D_803B75A0 = -1;
    do {
        digit = value % 10 + '0';
        draw_text_char(context, digit);
        value /= 10;
    } while (value != 0);
    D_803B75A0 = 1;
}
