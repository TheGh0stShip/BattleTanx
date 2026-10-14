#include "types.h"

extern void *gAudioSequenceHandle __asm__("D_80150350");
extern s32 D_80125710;

extern void alCSPSetVol(void *seqp, s16 volume) __asm__("func_8011B9A0");
extern void alCSPStop(void *seqp) __asm__("func_8011B9E0");

void stop_sequence_player(void) __asm__("func_80079D58");

void stop_sequence_player(void)
{
    alCSPSetVol(gAudioSequenceHandle, 0);
    alCSPStop(gAudioSequenceHandle);
    D_80125710 = -1;
}
