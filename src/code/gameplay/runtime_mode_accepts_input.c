#include "types.h"

extern u32 *D_801B4ABC;

s32 runtime_mode_accepts_input(void) __asm__("func_8007C728");

s32 runtime_mode_accepts_input(void)
{
    switch (*D_801B4ABC) {
    case 0:
    case 3:
    case 4:
    case 6:
        return 1;
    default:
        return 0;
    }
}
