#include "types.h"

extern f32 gSecondsPerGameTick __asm__("D_80074500");
extern s32 get_elapsed_game_ticks(void) __asm__("func_8007B1DC");

f32 get_elapsed_game_seconds(void) __asm__("func_800E21B4");

f32 get_elapsed_game_seconds(void)
{
    return (f32)get_elapsed_game_ticks() * gSecondsPerGameTick;
}
