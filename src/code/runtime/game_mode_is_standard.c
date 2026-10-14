#include "types.h"

extern s32 D_80137904;

s32 game_mode_is_standard(void) __asm__("func_800EC3D0");

s32 game_mode_is_standard(void)
{
    register u32 mode __asm__("$4") = D_80137904;
    register s32 in_range __asm__("$3") = mode < 11;
    register s32 result __asm__("$2") = 0;

    if (in_range) {
        result = mode != 0;
    }
    return result;
}
