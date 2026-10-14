#include "types.h"

typedef struct Listener {
    f32 value00;
    f32 value04;
    u8 pad08[0x24];
} Listener;

typedef struct ListenerOwner {
    u8 pad000[0x5A4];
    Listener listeners[1];
} ListenerOwner;

extern s32 find_sound_instance(s32 soundId, s32 index) __asm__("func_800796F0");
extern void set_sound_instance_value(s32 instance, s32 value) __asm__("func_800799D0");
extern s32 func_8007AAA0(void);
extern f64 D_80071518;
extern f64 D_80071520;
extern f64 D_80071528;
extern f32 D_80071530;
extern ListenerOwner *D_801C9170;

s32 start_sound_scaled_by_listener_distance(s32 soundId, f32 x, f32 z) __asm__("func_80085B4C");

/* Uses the loudest inverse-square falloff across all listeners; starts the sound only above a threshold. */
s32 start_sound_scaled_by_listener_distance(s32 soundId, f32 x, f32 z)
{
    s32 count;
    s32 i;
    f32 best;
    f32 dx;
    f32 dz;
    f32 level;
    ListenerOwner *owner;
    s32 instance;

    count = func_8007AAA0();
    best = 0.0f;
    owner = D_801C9170;
    for (i = 0; i < count; i++) {
        dx = x - owner->listeners[i].value04;
        dz = z - owner->listeners[i].value00;
        level = D_80071520 / ((dx * dx + dz * dz) * D_80071518 + D_80071520);
        if (best < level) {
            best = level;
        }
    }
    if (D_80071528 < best) {
        instance = find_sound_instance(soundId, 0);
        set_sound_instance_value(instance, (s16)(best * D_80071530));
        return instance;
    }
    return -1;
}
