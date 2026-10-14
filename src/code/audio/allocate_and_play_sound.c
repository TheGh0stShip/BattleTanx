#include "types.h"

typedef struct SoundBank {
    u8 pad00[0x10];
    void *sounds[1];
} SoundBank;

extern void *gActiveSound __asm__("D_80150380");
extern SoundBank *gSoundBank __asm__("D_80150390");
extern s16 gSoundSlotFree[32] __asm__("D_801B4A58");
extern u16 gAudioControlValue __asm__("D_80125774");
extern s16 allocate_sound(void *player, void *sound) __asm__("func_8011C210");
extern void deallocate_sound(void *player, s16 id) __asm__("func_8011C2B0");
extern s32 dispatch_audio_commands(void *player) __asm__("func_8011C300");
extern void play_sound(void *player) __asm__("func_8011CA30");
extern void set_sound_priority(void *player, s16 id, u8 priority) __asm__("func_8011CB60");
extern void set_sound_id(void *sound, s16 id) __asm__("func_8011CB90");
extern void set_sound_volume(void *sound, s16 volume) __asm__("func_8011CBB0");

s16 allocate_and_play_sound(u32 index, s32 priority) __asm__("func_800796F0");

s16 allocate_and_play_sound(u32 index, s32 priority) {
    s16 id;
    s32 i;
    u32 volume;

    id = allocate_sound(gActiveSound, gSoundBank->sounds[index]);
    if (id == -1) {
        for (i = 0; i < 32; i++) {
            if (gSoundSlotFree[i] != 0) {
                set_sound_id(gActiveSound, i);
                if (dispatch_audio_commands(gActiveSound) == 0) {
                    deallocate_sound(gActiveSound, i);
                    id = allocate_sound(gActiveSound, gSoundBank->sounds[index]);
                    break;
                }
            }
        }
    }
    if (id != -1) {
        gSoundSlotFree[id] = 0;
        set_sound_id(gActiveSound, id);
        set_sound_priority(gActiveSound, id, priority + 5);
        volume = gAudioControlValue;
        if (index >= 0x2B) {
            volume = (volume * 6) / 5;
        }
        set_sound_volume(gActiveSound, volume);
        play_sound(gActiveSound);
    }
    return id;
}
