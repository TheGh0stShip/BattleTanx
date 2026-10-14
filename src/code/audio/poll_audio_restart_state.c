#include "types.h"

extern s32 audio_restarts_disabled(void) __asm__("func_800EC644");

void poll_audio_restart_state(void) __asm__("func_800DDC3C");

void poll_audio_restart_state(void)
{
    audio_restarts_disabled();
}
