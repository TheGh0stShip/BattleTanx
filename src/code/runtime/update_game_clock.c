#include "types.h"

#define USEC_PER_SECOND 1000000
#define GAME_TICKS_PER_SECOND 30
#define GAME_MODE_PAUSED 2

extern u64 osClockRate __asm__("D_80145DA0");
extern u64 gClockPreviousTime __asm__("D_801257A0");
extern u64 gClockStartTime __asm__("D_801257A8");
extern f32 gClockFrameScale __asm__("D_801257B0");
extern s32 gClockFrameCounter __asm__("D_801257B4");
extern s32 gFramesPerSecond __asm__("D_80125788");
extern s32 gGameMode __asm__("D_8012578C");
extern u64 gClockFrameTime __asm__("D_801B4AC8");
extern s32 gGameTicks __asm__("D_801B4AA8");
extern f32 D_800710F4;
extern f32 D_800710F8;

extern u64 osGetTime(void) __asm__("func_801120A0");
extern s32 game_mode_is_3_through_6(void) __asm__("func_8007C6D8");
extern void update_timing_square(void) __asm__("func_800862B4");
extern void func_800862E8(void);
extern u32 next_random_u32(void) __asm__("func_800F38F4");

void update_game_clock(void) __asm__("func_8007AD2C");

void update_game_clock(void)
{
    u64 now;
    u64 elapsed;
    s32 threshold;

    now = osGetTime();
    if (now * USEC_PER_SECOND / osClockRate / USEC_PER_SECOND
        > gClockStartTime * USEC_PER_SECOND / osClockRate / USEC_PER_SECOND) {
        gFramesPerSecond = gClockFrameCounter;
        gClockFrameCounter = 0;
        threshold = 20;
        if (game_mode_is_3_through_6()) {
            threshold = 26;
        }
        if (gFramesPerSecond > threshold) {
            func_800862E8();
        } else {
            update_timing_square();
        }
    } else {
        gClockFrameCounter++;
        next_random_u32();
    }
    if (gGameMode != GAME_MODE_PAUSED) {
        elapsed = now - gClockStartTime;
        gClockPreviousTime += elapsed;
        gClockFrameScale = (f32)(elapsed * USEC_PER_SECOND / osClockRate) * D_800710F4 / D_800710F8;
    }
    gClockStartTime = now;
    gGameTicks = (gClockPreviousTime - gClockFrameTime) * USEC_PER_SECOND / osClockRate * GAME_TICKS_PER_SECOND
                 / USEC_PER_SECOND;
}
