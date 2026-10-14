#include "types.h"

extern u8 gAudioSequenceState __asm__("D_803276E0");

void reset_audio_sequence_state(void) __asm__("func_800AC2D0");

void reset_audio_sequence_state(void)
{
    gAudioSequenceState = 0;
}
