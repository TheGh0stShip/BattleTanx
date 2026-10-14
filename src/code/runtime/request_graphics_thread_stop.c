#include "types.h"

extern s32 gGraphicsThreadStopRequested __asm__("D_801502E0");

void request_graphics_thread_stop(void) __asm__("func_800794B4");

void request_graphics_thread_stop(void)
{
    gGraphicsThreadStopRequested = 1;
}
