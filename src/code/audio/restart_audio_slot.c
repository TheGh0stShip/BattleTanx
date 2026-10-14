#include "types.h"

extern s32 gAudioSlotMap[] __asm__("D_802DF540");
extern s32 gAudioSlotRestartTimers[] __asm__("D_802DF570");

extern s32 audio_restarts_disabled(void) __asm__("func_800EC644");

void restart_audio_slot(s32 slot) __asm__("func_800A8FB8");

void restart_audio_slot(s32 slot)
{
    s32 mappedSlot;

    mappedSlot = gAudioSlotMap[slot];
    if (mappedSlot >= 0 && audio_restarts_disabled() == 0) {
        gAudioSlotRestartTimers[mappedSlot] = 1;
    }
}
