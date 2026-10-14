#include "types.h"

extern void *gActiveSound __asm__("D_80150380");
extern void set_sound_id(void *sound, s16 id) __asm__("func_8011CB90");
extern void set_sound_value(void *sound, f32 value) __asm__("func_8011CB00");

void configure_active_sound(s32 id, f32 value) __asm__("func_80079A5C");

void configure_active_sound(s32 id, f32 value)
{
    if (id != -1) {
        set_sound_id(gActiveSound, (s16)id);
        set_sound_value(gActiveSound, value);
    }
}
