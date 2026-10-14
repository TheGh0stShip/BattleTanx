#include "types.h"

extern void *gActiveSound __asm__("D_80150380");
extern void set_sound_id(void *sound, s16 id) __asm__("func_8011CB90");
extern void set_sound_byte_value(void *sound, u8 value) __asm__("func_8011CAA0");

void set_sound_duration(s32 id, s32 duration) __asm__("func_80079AB4");

void set_sound_duration(s32 id, s32 duration)
{
    if (id != -1) {
        set_sound_id(gActiveSound, (s16)id);
        set_sound_byte_value(gActiveSound, duration);
    }
}
