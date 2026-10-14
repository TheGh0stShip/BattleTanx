#include "types.h"

extern void *gActiveSound __asm__("D_80150380");
extern void set_sound_id(void *sound, s16 id) __asm__("func_8011CB90");
extern void set_sound_volume(void *sound, s16 volume) __asm__("func_8011CBB0");
extern u16 gAudioControlValue __asm__("D_80125774");

void set_sound_scaled_volume(s32 id, s16 volume) __asm__("func_800799D0");

void set_sound_scaled_volume(s32 id, s16 volume) {
    s16 scaled = (volume * gAudioControlValue) / 32767;

    if (id != -1) {
        set_sound_id(gActiveSound, id);
        set_sound_volume(gActiveSound, scaled);
    }
}
