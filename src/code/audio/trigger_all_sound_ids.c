#include "types.h"

extern void *gActiveSound __asm__("D_80150380");
extern void set_sound_id(void *sound, s16 id) __asm__("func_8011CB90");
extern s32 dispatch_audio_commands(void *queue) __asm__("func_8011C300");
extern void func_8011CC10(void *sound);

void trigger_all_sound_ids(void) __asm__("func_80079948");

void trigger_all_sound_ids(void)
{
    s32 id;

    for (id = 0; id < 32; id++) {
        set_sound_id(gActiveSound, id);
        if (dispatch_audio_commands(gActiveSound) == 1) {
            func_8011CC10(gActiveSound);
        }
    }
}
