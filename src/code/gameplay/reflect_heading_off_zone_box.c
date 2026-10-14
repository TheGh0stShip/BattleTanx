#include "types.h"

typedef struct QuadPoint {
    f32 x;
    f32 z;
} QuadPoint;

typedef struct BounceZone {
    u8 pad00[0xC];
    void *owner;
    f32 centerZ;
    f32 centerX;
    s32 value18;
    s32 areaIndex;
    s32 value20;
} BounceZone;

typedef struct BounceKind {
    u8 pad00[0x8];
    s32 kind;
} BounceKind;

typedef struct BounceMover {
    f32 x;
    f32 y;
    f32 z;
    u16 heading;
    u8 pad0E[0x2];
    s32 value10;
    s32 value14;
} BounceMover;

typedef struct BounceResult {
    s32 action;
    u8 pad04[0x8];
    s16 heading;
} BounceResult;

extern s32 start_sound_scaled_by_listener_distance(s32 soundId, f32 x, f32 z) __asm__("func_80085B4C");
extern s32 point_off_quad_edges(QuadPoint *quad, QuadPoint *point) __asm__("func_80094774");
extern void spawn_attached_position_effect(void *owner, f32 *pos, u16 value) __asm__("func_800F2630");
extern f32 angle_sin(u16 angle) __asm__("func_800F3AE0");
extern f32 angle_cos(u32 angle) __asm__("func_800F3B40");
extern s32 radians_to_angle(f32 radians) __asm__("func_800F3BE4");
extern void area_box_corners(s32 index, QuadPoint *out) __asm__("func_80108E74");
extern float sqrtf(float);

void reflect_heading_off_zone_box(BounceZone *zone, BounceKind *kind, BounceMover *mover, BounceResult *result) __asm__("func_800F2270");

void reflect_heading_off_zone_box(BounceZone *zone, BounceKind *kind, BounceMover *mover, BounceResult *result)
{
    QuadPoint probe;
    QuadPoint quad[4];
    f32 offset[3];
    f32 dx;
    f32 dz;
    f32 length;
    s32 angle;
    s32 mid;

    switch (kind->kind) {
    case 2:
    case 0xC:
    case 0x16:
    case 0x22:
        if (mover->value14 != zone->value20) {
            probe.z = mover->x + angle_sin(mover->heading);
            probe.x = mover->z + angle_cos(mover->heading);
            area_box_corners(zone->areaIndex, quad);
            if (point_off_quad_edges(quad, &probe) != 0) {
                dx = mover->x - zone->centerX;
                dz = mover->z - zone->centerZ;
                length = sqrtf(dx * dx + dz * dz);
                dx /= length;
                dz /= length;
                if (-dx < 0.0f) {
                    angle = -radians_to_angle(-dz);
                } else {
                    angle = radians_to_angle(-dz);
                }
                mid = (mover->heading + (u16)angle + 0x8000) >> 1;
                result->action = 7;
                result->heading = (u16)mid * 2 - mover->heading;
                offset[0] = mover->x - zone->centerX;
                offset[1] = mover->y;
                offset[2] = mover->z - zone->centerZ;
                spawn_attached_position_effect(zone->owner, offset, (u16)(mid + 0x4000));
                start_sound_scaled_by_listener_distance(0x21, mover->x, mover->z);
                zone->value18 -= mover->value10;
                return;
            }
        }
        break;
    }
    result->action = 1;
}
