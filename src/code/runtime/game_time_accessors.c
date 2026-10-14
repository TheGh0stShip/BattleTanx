#include "types.h"

extern s32 gElapsedGameTicks __asm__("D_801B4AA8");
extern f32 gTicksPerSecond __asm__("D_800710FC");

s32 get_elapsed_game_ticks(void) __asm__("func_8007B1DC");
s32 seconds_to_game_ticks(f32 seconds) __asm__("func_8007B1EC");

s32 get_elapsed_game_ticks(void)
{
    return gElapsedGameTicks;
}

s32 seconds_to_game_ticks(f32 seconds)
{
    return (s32)(seconds * gTicksPerSecond);
}
