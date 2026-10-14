#include "types.h"

typedef struct SoundRampUnit {
    u8 pad00[0x3B4];
    f32 value3B4;
    u8 pad3B8[0x464 - 0x3B8];
    u8 cooldown464;
} SoundRampUnit;

extern s32 entity_state_is_one(SoundRampUnit *unit) __asm__("func_800E3470");
extern s32 find_sound_instance(s32 soundId, s32 index) __asm__("func_800796F0");
extern void set_sound_scaled_volume(s32 instance, s16 volume) __asm__("func_800799D0");
extern f64 D_800723B0;
extern f32 D_800723B8;
extern f32 D_800723BC;

void unit_update_sound_ramp(SoundRampUnit *unit, s32 soundId) __asm__("func_80099CD8");

void unit_update_sound_ramp(SoundRampUnit *unit, s32 soundId) {
    s32 instance;
    f32 value;

    if (unit->cooldown464 == 0 && D_800723B0 < unit->value3B4 && entity_state_is_one(unit) != 0) {
        instance = find_sound_instance(soundId, 0);
        value = unit->value3B4;
        if (value < D_800723B8) {
            set_sound_scaled_volume(instance, (s16)(s32)(value * 2.0f * D_800723BC));
        }
        unit->cooldown464 = 0x20;
    }
}
