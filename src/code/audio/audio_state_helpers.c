#include "types.h"

typedef struct AudioModeState {
    s32 mode;
    s32 currentValue;
    s32 pad08;
    s32 values[5];
} AudioModeState;

extern AudioModeState gAudioModeState __asm__("D_803275F0");

extern void dispatch_audio_command(s32 command) __asm__("func_80122130");

void dispatch_audio_command_65(void) __asm__("func_800AB91C");
void dispatch_audio_command_66(void) __asm__("func_800AB93C");
s32 select_audio_mode(u32 mode) __asm__("func_800AB95C");

void dispatch_audio_command_65(void)
{
    dispatch_audio_command(0x41);
}

void dispatch_audio_command_66(void)
{
    dispatch_audio_command(0x42);
}

s32 select_audio_mode(u32 mode)
{
    s32 previousMode;

    previousMode = gAudioModeState.mode;
    switch (mode) {
    case 0:
        gAudioModeState.mode = 0;
        gAudioModeState.currentValue = gAudioModeState.values[0];
        break;
    case 1:
        gAudioModeState.mode = 1;
        gAudioModeState.currentValue = gAudioModeState.values[1];
        break;
    case 2:
        gAudioModeState.mode = 2;
        gAudioModeState.currentValue = gAudioModeState.values[2];
        break;
    case 3:
        gAudioModeState.mode = 3;
        gAudioModeState.currentValue = gAudioModeState.values[3];
        break;
    case 4:
        gAudioModeState.mode = 4;
        gAudioModeState.currentValue = gAudioModeState.values[4];
        break;
    }
    return previousMode;
}
