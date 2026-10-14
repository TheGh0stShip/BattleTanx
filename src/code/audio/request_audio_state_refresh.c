#include "types.h"

extern s32 gAudioStateRefreshPending __asm__("D_802E17D0");

void request_audio_state_refresh(void) __asm__("func_800A8ECC");

void request_audio_state_refresh(void)
{
    gAudioStateRefreshPending = 1;
}
