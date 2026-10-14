#include "types.h"

s32 string_length(const u8 *text) __asm__("func_800B9C0C");

s32 string_length(const u8 *text)
{
    s32 length = 0;
    while (*text++ != 0) {
        length++;
    }
    return length;
}
