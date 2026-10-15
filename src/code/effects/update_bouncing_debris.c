#include "types.h"

typedef struct DebrisEffect {
    u8 pad00[0xC];
    f32 x;
    f32 y;
    f32 z;
    f32 vx;
    f32 vy;
    f32 vz;
    u16 timer;
    u16 spin;
    u8 value28;
    u8 pad29[0x3];
    s32 ignore;
    s32 sound;
} DebrisEffect;

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

extern s32 find_sound_instance(s32 soundId, s32 index) __asm__("func_800796F0");
extern void func_800798C0(s32);
extern void func_8008C2DC(u8 value);
extern void spawn_effect_kind_26(f32 *position, s32 variant) __asm__("func_800ED8C0");
extern s32 start_sound_scaled_by_listener_distance(s32 soundId, f32 x, f32 z) __asm__("func_80085B4C");
extern s32 find_segment_hit(PointZX *start, PointZX *end, s32 mode, SegmentHit *hit, s32 arg4) __asm__("func_8010874C");

void update_bouncing_debris(DebrisEffect *e, s32 *status) __asm__("func_800F2AE4");

void update_bouncing_debris(DebrisEffect *e, s32 *status)
{
    f32 next[3];
    PointZX start;
    PointZX end;
    SegmentHit hit;
    f32 dot;

    if (--e->timer == 0x32) {
        e->sound = find_sound_instance(0x14, 0);
    }
    if (e->timer == 0) {
        func_8008C2DC(e->value28);
        func_800798C0(e->sound);
        spawn_effect_kind_26(&e->x, 8);
        find_sound_instance(0xB, 0);
        *status = 2;
    }
    e->vy -= 2.0f;
    e->spin += 0x800;
    next[0] = e->x + e->vx;
    next[2] = e->z + e->vz;
    e->y += e->vy;
    if (e->y <= 15.0f) {
        e->vx -= e->vx * 0.05f;
        e->vz -= e->vz * 0.05f;
        e->vy = -e->vy;
        e->y = 15.0f;
        if (e->vy > 5.0f) {
            start_sound_scaled_by_listener_distance(0x1A, e->x, e->z);
        }
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
        e->vx = (dot * hit.normalX + e->vx) * 2.0f - e->vx;
        e->vz = (dot * hit.normalZ + e->vz) * 2.0f - e->vz;
        e->vx -= e->vx * 0.5f;
        e->vz -= e->vz * 0.5f;
        e->spin = -e->spin;
        e->ignore = -1;
    } else {
        e->x = next[0];
        e->z = next[2];
    }
}
