#include "types.h"

extern s32 gAudioSlotMap[] __asm__("D_802DF540");
extern s32 gAudioSlotRestartTimers[] __asm__("D_802DF570");
extern s32 D_802DF580[];
extern s32 D_802DF590[];
extern s32 D_802DF5A0[];

extern s32 audio_restarts_disabled(void) __asm__("func_800EC644");

void configure_audio_slot(s32 slot, s32 value, s32 param, s32 period) __asm__("func_800A8EF8");

void configure_audio_slot(s32 slot, s32 value, s32 param, s32 period)
{
    s32 mappedSlot;

    mappedSlot = gAudioSlotMap[slot];
    if (mappedSlot >= 0 && audio_restarts_disabled() == 0) {
        D_802DF580[mappedSlot] = (param = (param != 0) ? param : 1);
        D_802DF590[mappedSlot] = -((period > 0) ? period : 1);
        D_802DF5A0[mappedSlot] = -1;
        gAudioSlotRestartTimers[mappedSlot] = value;
    }
}
