#include "types.h"

extern s32 format_string(char *dst, char *fmt, ...) __asm__("func_8011CC84");
extern char D_80071560[];
extern char D_80071564[];

char *format_zero_padded_number(s32 value, s32 digits, char *out) __asm__("func_80086378");

static inline s32 int_power(s32 base, s32 exponent)
{
    s32 result;
    s32 i;

    result = 1;
    for (i = 0; i < exponent; i++) {
        result *= base;
    }
    return result;
}

char *format_zero_padded_number(s32 value, s32 digits, char *out)
{
    char buffer[16];

    format_string(buffer, D_80071560, value + int_power(10, digits));
    format_string(out, D_80071564, buffer + 1);
    return out;
}
