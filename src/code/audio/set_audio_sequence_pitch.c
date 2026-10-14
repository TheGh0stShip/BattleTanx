#include "types.h"

extern void *gAudioSequenceHandle __asm__("D_80150350");
extern void set_sequence_pitch(void *handle, s32 pitch) __asm__("func_8011B9A0");

void set_audio_sequence_pitch(s16 pitch) __asm__("func_80079BF4");

void set_audio_sequence_pitch(s16 pitch)
{
    set_sequence_pitch(gAudioSequenceHandle, pitch);
}
