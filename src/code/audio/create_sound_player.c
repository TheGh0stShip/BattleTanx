#include "types.h"

typedef struct SoundPlayerConfig {
    s32 maxSounds;
    s32 maxEvents;
    void *heap;
} SoundPlayerConfig;

extern void *alHeapDBAlloc(u8 *file, s32 line, void *heap, s32 num, s32 size) __asm__("func_80112140");
extern void func_8011C8F4(void *player, SoundPlayerConfig *config);
extern u8 gAudioHeap[] __asm__("D_80150340");
extern void *gActiveSound __asm__("D_80150380");

void create_sound_player(void) __asm__("func_80079FA4");

void create_sound_player(void)
{
    SoundPlayerConfig config;

    config.maxSounds = 0x20;
    config.maxEvents = 0x40;
    config.heap = gAudioHeap;
    gActiveSound = alHeapDBAlloc(0, 0, gAudioHeap, 1, 0x54);
    func_8011C8F4(gActiveSound, &config);
}
