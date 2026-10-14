#include "types.h"

typedef struct EffectMarker {
    u8 pad00[0xC];
    void *motion;
    f32 y;
    f32 x;
} EffectMarker;

extern EffectMarker *allocate_effect_marker(s32 pool, s32 type, s32 size) __asm__("func_8008AD10");
extern void *create_effect_motion(EffectMarker *marker, s32 x, s32 y, s32 minX, s32 maxX,
                                  s32 minY, s32 maxY, s32 mode, s32 flags) __asm__("func_80106D18");

void spawn_effect_marker(f32 x, f32 y, s32 extent) __asm__("func_800A7550");

void spawn_effect_marker(f32 x, f32 y, s32 extent)
{
    EffectMarker *marker;
    s32 negativeExtent;

    marker = allocate_effect_marker(0, 0x1F, 0x18);
    if (marker != 0) {
        negativeExtent = -extent;
        marker->motion = create_effect_motion(marker, (s32)x, (s32)y, negativeExtent, extent,
                                              negativeExtent, extent, 2, 0);
        marker->x = x;
        marker->y = y;
    }
}
