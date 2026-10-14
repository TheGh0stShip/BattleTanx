#include "types.h"

extern s32 find_sound_instance(s32 soundId, s32 index) __asm__("func_800796F0");
extern void set_sound_instance_value(s32 instance, s32 value) __asm__("func_800799D0");

void find_sound_38(void) __asm__("func_800ABF1C");
void set_sound_38_value_19114(void) __asm__("func_800ABF40");
void set_sound_38_value_25088(void) __asm__("func_800ABF70");

void find_sound_38(void)
{
    find_sound_instance(0x26, 0);
}

void set_sound_38_value_19114(void)
{
    set_sound_instance_value(find_sound_instance(0x26, 0), 0x4AAA);
}

void set_sound_38_value_25088(void)
{
    set_sound_instance_value(find_sound_instance(0x26, 0), 0x6200);
}
