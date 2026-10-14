#include "types.h"

extern void *gActiveSound __asm__("D_80150380");
extern void set_sound_id(void *sound, s16 id) __asm__("func_8011CB90");
extern s32 dispatch_audio_commands(void *queue) __asm__("func_8011C300");
extern void func_8011CC10(void *sound);
extern s16 D_801B4A58[];

s32 set_and_trigger_sound(s32 id) __asm__("func_800798C0");

s32 set_and_trigger_sound(s32 id)
{
    if (id != -1) {
        set_sound_id(gActiveSound, id);
        if (D_801B4A58[id] == 0 || dispatch_audio_commands(gActiveSound) == 1) {
            func_8011CC10(gActiveSound);
        }
    }
    return -1;
}
