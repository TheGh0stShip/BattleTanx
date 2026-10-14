#include "types.h"

extern void *gCurrentGameState __asm__("D_801B4ABC");

void *get_current_game_state(void) __asm__("func_8007AAF4");

void *get_current_game_state(void)
{
    return gCurrentGameState;
}
