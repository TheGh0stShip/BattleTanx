#include "types.h"

extern s32 gFrameEventCounter __asm__("D_803C4D70");

void increment_frame_event_counter(void) __asm__("func_8010D984");
void reset_frame_event_counter(void) __asm__("func_8010D9A0");

void increment_frame_event_counter(void)
{
    gFrameEventCounter += 1;
}

void reset_frame_event_counter(void)
{
    gFrameEventCounter = 0;
}
