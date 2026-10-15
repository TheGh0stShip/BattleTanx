#include "types.h"

typedef struct GrenadeEffect {
    u8 pad00[0xC];
    f32 x;
    f32 y;
    f32 z;
    f32 vx;
    f32 vy;
    f32 vz;
    u16 timer;
    u16 spin;
    u8 owner;
    u8 pad29[0x3];
    s32 ignore;
} GrenadeEffect;

typedef struct PointZX {
    f32 z;
    f32 x;
} PointZX;

typedef struct SegmentHit {
    f32 value00;
    f32 x;
    f32 value08;
    f32 z;
    f32 normalZ;
    f32 normalX;
} SegmentHit;

extern void spawn_effect_kind_26(f32 *position, s32 variant) __asm__("func_800ED8C0");
extern void func_800902BC(f32 *position, s32 arg1);
extern void func_8009F958(GrenadeEffect *e, PointZX *center, f32 radius, f32 damage, s32 owner);
extern s32 start_sound_scaled_by_listener_distance(s32 soundId, f32 x, f32 z) __asm__("func_80085B4C");
extern void func_80079A5C(s32 sound, f32 value);
extern f32 random_float_range(f32 range) __asm__("func_800F3880");
extern s32 find_segment_hit(PointZX *start, PointZX *end, s32 mode, SegmentHit *hit, s32 arg4) __asm__("func_8010874C");

void update_bouncing_grenade(GrenadeEffect *e, s32 *status) __asm__("func_800F3490");

void update_bouncing_grenade(GrenadeEffect *e, s32 *status)
{
    f32 next[3];
    PointZX start;
    PointZX end;
    SegmentHit hit;
    f32 dot;

    start.x = e->x;
    start.z = e->z;
    if (--e->timer == 0) {
        spawn_effect_kind_26(&e->x, 0x1A);
        func_800902BC(&e->x, 4);
        func_8009F958(e, &start, 100.0f, 22.0f, e->owner);
        start_sound_scaled_by_listener_distance(5, e->x, e->z);
        *status = 2;
    }
    e->vy -= 2.0f;
    e->spin += 0x800;
    next[0] = e->x + e->vx;
    next[2] = e->z + e->vz;
    e->y += e->vy;
    if (e->y <= 15.0f) {
        e->vx -= e->vx * 0.15f;
        e->vz -= e->vz * 0.15f;
        e->vy = -e->vy * 0.8f;
        e->y = 15.0f;
    } else {
        e->vx -= e->vx * 0.01f;
        e->vz -= e->vz * 0.01f;
    }
    start.x = e->x;
    start.z = e->z;
    end.x = next[0];
    end.z = next[2];
    if (find_segment_hit(&start, &end, 0x10, &hit, e->ignore)) {
        dot = hit.normalX * -e->vx + hit.normalZ * -e->vz;
        e->vx = ((dot * hit.normalX + e->vx) * 2.0f - e->vx) * (random_float_range(0.6f) + 0.7f);
        e->vz = ((dot * hit.normalZ + e->vz) * 2.0f - e->vz) * (random_float_range(0.6f) + 0.7f);
        e->vx -= e->vx * 0.6f;
        e->vz -= e->vz * 0.6f;
        e->ignore = 0;
        e->spin = -e->spin;
        if (e->vy > 5.0f) {
            func_80079A5C(start_sound_scaled_by_listener_distance(0x1A, e->x, e->z), 2.0f);
        }
    } else {
        e->x = next[0];
        e->z = next[2];
    }
}
