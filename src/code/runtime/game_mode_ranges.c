#include "types.h"
typedef struct GameModeState { u32 mode; } GameModeState;
extern GameModeState *D_801B4ABC;
s32 game_mode_is_3_through_6(void) __asm__("func_8007C6D8");
s32 game_mode_is_3_through_7(void) __asm__("func_8007C700");
s32 game_mode_is_3_through_6(void)
{
    u32 mode = D_801B4ABC->mode;
    if (mode < 7) {
        if (mode >= 3) {
            return 1;
        }
    }
    return 0;
}

s32 game_mode_is_3_through_7(void)
{
    u32 mode = D_801B4ABC->mode;
    if (mode < 8) {
        if (mode >= 3) {
            return 1;
        }
    }
    return 0;
}
