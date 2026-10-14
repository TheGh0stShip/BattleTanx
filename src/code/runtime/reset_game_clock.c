#include "types.h"

extern u64 gClockPreviousTime __asm__("D_801257A0");
extern u64 gClockStartTime __asm__("D_801257A8");
extern f32 gClockFrameScale __asm__("D_801257B0");
extern u64 gClockFrameTime __asm__("D_801B4AC8");
extern s32 gGameTicks __asm__("D_801B4AA8");
extern f32 D_800710F0;

extern u64 osGetTime(void) __asm__("func_801120A0");

void reset_game_clock(void) __asm__("func_8007ACC4");

void reset_game_clock(void)
{
    u64 now;

    now = osGetTime();
    gClockStartTime = now;
    gClockPreviousTime = now;
    gClockFrameTime = now;
    gGameTicks = 0;
    gClockFrameScale = D_800710F0;
}
