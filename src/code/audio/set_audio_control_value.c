#include "types.h"

extern s16 gAudioControlValue __asm__("D_80125774");

void set_audio_control_value(s32 value) __asm__("func_800799C0");

void set_audio_control_value(s32 value)
{
    gAudioControlValue = value;
}
