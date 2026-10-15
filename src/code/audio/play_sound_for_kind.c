#include "types.h"

extern s32 find_sound_instance(s32 soundId, s32 index) __asm__("func_800796F0");

void play_sound_for_kind(u32 kind) __asm__("func_800D1EBC");

void play_sound_for_kind(u32 kind) {
    switch (kind) {
    case 0:
        find_sound_instance(0x26, 0);
        break;
    case 1:
        find_sound_instance(0x1C, 0);
        break;
    case 2:
        find_sound_instance(1, 0);
        break;
    case 3:
        find_sound_instance(3, 0);
        break;
    case 4:
        find_sound_instance(0xD, 0);
        break;
    }
}
