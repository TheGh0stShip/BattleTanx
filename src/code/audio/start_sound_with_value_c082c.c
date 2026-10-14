#include "types.h"

extern s32 find_sound_instance(s32 soundId, s32 index) __asm__("func_800796F0");
extern void set_sound_instance_value(s32 instance, s32 value) __asm__("func_800799D0");

s32 start_sound_with_value_c082c(s32 soundId, s16 value) __asm__("func_800C082C");

s32 start_sound_with_value_c082c(s32 soundId, s16 value)
{
    s32 instance = find_sound_instance(soundId, 0);
    set_sound_instance_value(instance, value);
    return instance;
}
