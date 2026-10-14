#include "types.h"

extern s32 find_sound_instance(s32 soundId, s32 index) __asm__("func_800796F0");
extern void set_sound_duration(s32 sound, s32 duration) __asm__("func_80079AB4");

s32 play_sound_for_duration(s32 context, s32 soundId) __asm__("func_800EDAAC");

s32 play_sound_for_duration(s32 context, s32 soundId)
{
    set_sound_duration(find_sound_instance(soundId, 0), 0x64);
    return 1;
}
