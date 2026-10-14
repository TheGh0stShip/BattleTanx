#include "types.h"

typedef struct EffectPoint {
    f32 x;
    f32 y;
    f32 z;
} EffectPoint;

typedef struct DelayedBlastEffect {
    u8 pad00[0xC];
    f32 value0C;
    f32 value10;
    s32 value14;
    s32 pad18;
    s32 startTick;
    u8 pad20[0x7];
    u8 value27;
} DelayedBlastEffect;

extern s32 gGameTicks __asm__("D_801B4AA8");

extern void spawn_effect_kind_26(EffectPoint *position, s32 variant) __asm__("func_800ED8C0");
extern void func_80107170(s32 arg0);
extern s32 start_sound_scaled_by_listener_distance(s32 soundId, f32 x, f32 z) __asm__("func_80085B4C");
extern void notify_objects_near_point(DelayedBlastEffect *sender, f32 *point, f32 radius, f32 value,
                                      u8 flag) __asm__("func_8009F958");

void delayed_blast_effect_update(DelayedBlastEffect *effect, s32 *state) __asm__("func_8010DC0C");

void delayed_blast_effect_update(DelayedBlastEffect *effect, s32 *state)
{
    EffectPoint point;

    if (effect->startTick == 0) {
        point.x = effect->value10;
        point.y = 0.0f;
        point.z = effect->value0C;
        spawn_effect_kind_26(&point, 0xD);
        if (effect->value14 != 0) {
            func_80107170(effect->value14);
        }
        start_sound_scaled_by_listener_distance(5, effect->value10, effect->value0C);
        effect->startTick = gGameTicks;
    } else if (effect->startTick + 8 < gGameTicks) {
        notify_objects_near_point(effect, &effect->value0C, 108.0f, 20.0f, effect->value27);
        *state = 2;
    }
}
