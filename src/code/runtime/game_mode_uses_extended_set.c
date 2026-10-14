#include "types.h"

extern s32 gGameMode __asm__("D_80137904");

s32 game_mode_uses_extended_set(void) __asm__("func_800EC390");

s32 game_mode_uses_extended_set(void) {
    s32 mode = gGameMode;

    if ((u32)(mode - 2) < 2 || (mode == 7 | mode == 11)) {
        return 1;
    }
    return 0;
}
