#include "types.h"

typedef struct Vec3 {
    f32 x;
    f32 y;
    f32 z;
} Vec3;

typedef struct Corners {
    f32 points[4][2];
} Corners;

typedef struct AreaMarker {
    u8 pad00[0x20];
    s32 area;
    u8 active;
} AreaMarker;

extern void area_box_corners(s32 index, Corners *out) __asm__("func_80108E74");
extern void spawn_effect_kind_19(s32 a, s32 b, s32 c, s32 d, s32 e) __asm__("func_800F2E50");
extern f32 random_float_range(f32 range) __asm__("func_800F3880");
extern void spawn_kind24_burst(Vec3 *origin) __asm__("func_800F1E74");
extern void spawn_effect_kind_26(Vec3 *position, s32 variant) __asm__("func_800ED8C0");
extern f32 D_800749F4;
extern f32 D_800749F8;
extern f32 D_800749FC;
extern f32 D_80074A00;

void spawn_area_marker_effects(AreaMarker *marker) __asm__("func_800ECD30");

void spawn_area_marker_effects(AreaMarker *marker) {
    Vec3 center;
    Corners corners;
    Vec3 burst;
    f32 range;
    f32 offset;
    s32 i;

    area_box_corners(marker->area, &corners);
    center.x = (corners.points[0][1] + corners.points[2][1]) / D_800749F4;
    center.z = (corners.points[0][0] + corners.points[2][0]) / D_800749F4;
    center.y = D_800749F8;
    if (marker->active) {
        spawn_effect_kind_19(0x84, 0xFF, 0, 0xC, -1);
        i = 0;
        range = D_800749FC;
        offset = D_80074A00;
        do {
            burst.x = (center.x + random_float_range(range)) - offset;
            burst.y = center.y;
            burst.z = (center.z + random_float_range(range)) - offset;
            i++;
            spawn_kind24_burst(&burst);
        } while (i < 4);
        spawn_effect_kind_26(&center, 0x1B);
    } else {
        spawn_effect_kind_26(&center, 7);
    }
}
