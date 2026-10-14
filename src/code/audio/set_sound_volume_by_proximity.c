#include "types.h"

typedef struct ProximitySource {
    f32 y;
    f32 x;
    u8 pad08[0x24];
} ProximitySource;

typedef struct ProximitySourceTable {
    u8 pad00[0x5A4];
    ProximitySource sources[1];
} ProximitySourceTable;

extern s32 find_sound_instance(s32 soundId, s32 index) __asm__("func_800796F0");
extern void set_sound_scaled_volume(s32 instance, s16 volume) __asm__("func_800799D0");
extern s32 get_difficulty_level(void) __asm__("func_8007AAA0");
extern f64 D_80071538;
extern f64 D_80071540;
extern f64 D_80071548;
extern f32 D_80071550;
extern ProximitySourceTable *gProximitySourceTable __asm__("D_801C9170");

void set_sound_volume_by_proximity(s32 soundId, f32 x, f32 y, f32 scale) __asm__("func_80085C68");

void set_sound_volume_by_proximity(s32 soundId, f32 x, f32 y, f32 scale) {
    s32 count = get_difficulty_level();
    f32 best = 0.0f;
    s32 i;
    ProximitySourceTable *table = gProximitySourceTable;

    for (i = 0; i < count; i++) {
        f32 dx = x - table->sources[i].x;
        f32 dy = y - table->sources[i].y;
        f32 weight = D_80071540 / ((dx * dx + dy * dy) * D_80071538 + D_80071540);

        if (best < weight) {
            best = weight;
        }
    }
    if (best > D_80071548) {
        set_sound_scaled_volume(find_sound_instance(soundId, 0), scale * best * D_80071550);
    }
}
