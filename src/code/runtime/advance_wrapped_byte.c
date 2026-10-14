#include "types.h"

extern u8 D_80135820;

u32 advance_wrapped_byte(void) __asm__("func_800DDB94");

u32 advance_wrapped_byte(void)
{
    u8 previous = D_80135820;
    u8 current = previous + 1;
    u32 result;

    D_80135820 = current;
    if (current < 241) {
        result = (previous + 16) & 0xFF;
    } else {
        result = 15;
    }
    return result;
}
