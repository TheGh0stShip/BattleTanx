#include "types.h"

typedef struct AreaBox {
    s16 value00;
    s16 value02;
    s16 value04;
    s16 value06;
    s16 value08;
    s16 value0A;
    s16 value0C;
    s16 value0E;
    s16 value10;
} AreaBox;

typedef struct TurretMatrix {
    f32 m[16];
} TurretMatrix;

typedef struct Vec3 {
    f32 x;
    f32 y;
    f32 z;
} Vec3;

typedef struct PointZX {
    f32 z;
    f32 x;
} PointZX;

typedef struct HitObject {
    u8 pad00[0x8];
    s32 kind;
    struct HitObject *link;
} HitObject;

typedef struct SegmentHit {
    HitObject *object;
    f32 x;
    f32 y;
    f32 z;
    f32 normalZ;
    f32 normalX;
} SegmentHit;

typedef struct TargetUnit {
    u8 pad00;
    u8 active;
    u8 pad02[0x22];
    f32 x;
    u8 pad28[0x4];
    f32 z;
} TargetUnit;

typedef struct TurretOwner {
    u8 pad000[0x318];
    f32 rebuildTime;
    u8 pad31C[0x1C];
    s16 effectKind[4];
    s16 fireDelay[4];
} TurretOwner;

typedef struct Turret {
    u8 pad00[0xC];
    u8 flags;
    u8 kind;
    u8 cycle;
    u8 pad0F[0x3];
    union {
        u16 id;
        u8 b[2];
    } owner;
    s32 type;
    u16 heading;
    u8 pad1A[0x2];
    f32 z;
    f32 x;
    s32 area;
    s32 lastFire;
    s16 health;
    u16 targetId;
    u8 fade;
    u8 cooldown;
    u8 hasLos;
    u8 pad33;
    s32 aimTime;
    u16 aimHeading;
} Turret;

extern const TurretMatrix D_80072C24;
extern f32 D_801257B0;
extern s16 D_80125FC0[];
extern s16 D_80125FC8[];
extern Vec3 D_80125FD0[];
extern u16 D_80126010[];
extern s32 D_80126028[];
extern f32 D_80126038[];
extern u32 D_80126048[];
extern s32 D_80126058[];
extern f32 D_80126068[];
extern f32 D_80126080[];
extern s32 D_801B4AA8;

extern f32 sqrtf(f32 value);
extern void spawn_effect_kind_22(f32 *pos, f32 *velocity, f32 speed, u16 heading, u8 team, u8 effect, s16 kind,
                                 u16 flag, Turret *owner, u8 arg9) __asm__("func_8008E29C");
extern s32 start_sound_scaled_by_listener_distance(s32 soundId, f32 x, f32 z) __asm__("func_80085B4C");
extern TargetUnit *get_unit(s16 id) __asm__("func_800A03B8");
extern void find_nearest_enemy_unit(Turret *turret) __asm__("func_800A1170");
extern TurretOwner *get_entity_record(u16 index) __asm__("func_800A6688");
extern s32 func_800A68AC(u8 kind);
extern void set_yaw_transform(TurretMatrix *m, f32 x, f32 y, f32 z, u16 angle) __asm__("func_800A7744");
extern void transform_point_3x4(TurretMatrix *m, f32 *in, f32 *out) __asm__("func_800A7D10");
extern s32 entity_state_is_two(TargetUnit *unit) __asm__("func_800E3460");
extern void func_800E3C18(TargetUnit *unit, Turret *turret);
extern s32 spawn_beam_effect(f32 *pos, u16 heading, u8 owner, s16 kind, s32 arg4, s32 depth, Turret *ignore, u8 arg7)
    __asm__("func_800F0FD8");
extern u32 next_random_u32(void) __asm__("func_800F38F4");
extern f32 sinf_u16(u16 angle) __asm__("func_800F3AE0");
extern f32 cosf_u16(u16 angle) __asm__("func_800F3B40");
extern s32 cosine_to_angle(f32 cosine) __asm__("func_800F3BE4");
extern u16 angle_distance(u16 a, u16 b) __asm__("func_800F3D0C");
extern s32 create_effect_motion(Turret *t, s32 x, s32 z, s32 minX, s32 maxX, s32 minZ, s32 maxZ, s32 mode,
                                s32 flags) __asm__("func_80106D18");
extern void release_effect_motion(s32 handle) __asm__("func_80107170");
extern u8 find_objects_in_area(void *box, s32 capacity, void **results, s32 *count) __asm__("func_80107A14");
extern s32 find_segment_hit(PointZX *start, PointZX *end, s32 mode, SegmentHit *hit, s32 arg4) __asm__("func_8010874C");
extern void build_area_box(void *box, s32 x, s32 z, s32 minX, s32 maxX, s32 minZ, s32 maxZ, s32 angle)
    __asm__("func_80109268");

void update_turret(Turret *t, s32 *result) __asm__("func_800A16C0");

#define TURN_STEP(type) ((u16)(u32)(D_801257B0 * (f32)D_80125FC8[type]))

static inline s32 area_is_clear(f32 x, f32 y, s32 sizeIndex)
{
    void *results[16];
    AreaBox box;
    s32 count;
    f32 half;

    half = D_80126038[sizeIndex] * 45.0f;
    build_area_box(&box, x, y, -half, half, -half, half, 0);
    return !find_objects_in_area(&box, 16, results, &count);
}

void update_turret(Turret *t, s32 *result)
{
    s32 type;
    TurretOwner *owner;
    f32 scale;

    owner = get_entity_record(t->owner.id);
    type = t->type;
    scale = D_80126038[type];
    if (t->flags & 8) {
        if (D_801B4AA8 > t->lastFire) {
            if (area_is_clear(t->x, t->z, type)) {
                s32 hi = scale * 45.0f;

                t->lastFire = 0;
                t->flags &= 0xF6;
                t->health = D_80126010[t->type];
                t->fade = 0xFF;
                find_nearest_enemy_unit(t);
                t->area = create_effect_motion(t, t->x, t->z, scale * -45.0f, hi, scale * -45.0f, hi, 0xD6, 0);
            }
        }
        return;
    }
    if (t->fade != 0) {
        t->fade = (t->fade >= 16) ? t->fade - 16 : 0;
        return;
    }
    if (t->health <= 0) {
        release_effect_motion(t->area);
        if (t->flags & 0x14) {
            t->flags = (t->flags | 8) & 0xEF;
            t->lastFire = D_801B4AA8 + (s32)(owner->rebuildTime / 100.0f * 1800.0f * D_80126080[func_800A68AC(t->kind)]);
            return;
        }
        *result = 2;
        return;
    }
    if (!(next_random_u32() & 0xF)) {
        find_nearest_enemy_unit(t);
    }
    if (t->cooldown != 0) {
        t->cooldown--;
    }
    if (t->targetId != 0xFF) {
        TargetUnit *unit = get_unit(t->targetId);
        f32 dx;
        f32 dz;
        f32 distSq;
        s32 target;
        u16 heading;
        u16 diff;
        u16 fwd;
        u16 back;
        s32 delay;
        u16 dist;

        if (unit->active == 0) {
            return;
        }
        dx = unit->x - t->x;
        dz = unit->z - t->z;
        distSq = dx * dx + dz * dz;
        if (distSq > 25000000.0f) {
            return;
        }
        if ((dx != 0.0f) | (dz != 0.0f)) {
            if (dx < 0.0f) {
                target = -cosine_to_angle(dz / sqrtf(distSq));
            } else {
                target = cosine_to_angle(dz / sqrtf(distSq));
            }
        } else {
            target = 0;
        }
        heading = t->heading;
        fwd = target - heading;
        back = heading - target;
        if (fwd < back) {
            t->heading = heading + ((fwd >= TURN_STEP(type)) ? TURN_STEP(type) : fwd);
        } else {
            t->heading = heading - ((back >= TURN_STEP(type)) ? TURN_STEP(type) : back);
        }
        dist = angle_distance(t->heading, target);
        delay = owner->fireDelay[type];
        if (D_80126058[type] != 0) {
            delay = delay * D_80126068[t->cycle];
        }
        if (dist < 0x1000) {
            f32 fdelay = delay;
            f32 wait;
            f64 last;
            f64 w;
            f64 now;
            TurretMatrix m;
            f32 muzzle[3];
            f32 velocity[2];
            u16 aim;

            wait = entity_state_is_two(unit) ? fdelay * 4.0f : fdelay;
            w = wait;
            last = t->lastFire;
            now = D_801B4AA8;
            if (!((t->flags & 4) ? (last + w * D_80126080[func_800A68AC(t->kind)] < now) : (last + w < now))) {
                return;
            }
            m = D_80072C24;
            {
            Vec3 offset;
            PointZX start;
            PointZX end;
            SegmentHit hit;

            if (t->cooldown == 0) {
                t->cooldown = 16;
                set_yaw_transform(&m, t->x, 0.0f, t->z, t->heading);
                offset = D_80125FD0[type];
                offset.x *= scale;
                offset.y *= scale;
                offset.z *= scale;
                if (t->flags & 2) {
                    offset.x = -offset.x;
                }
                t->flags ^= 2;
                transform_point_3x4(&m, &offset.x, muzzle);
                start.x = muzzle[0];
                start.z = muzzle[2];
                end.x = unit->x;
                end.z = unit->z;
                if (find_segment_hit(&start, &end, 4, &hit, -1) == 0) {
                    t->hasLos = 0;
                } else if ((u32)hit.object < 3) {
                    t->hasLos = 0;
                } else if (hit.object->kind != 0 || (TargetUnit *)hit.object->link != unit) {
                    if (hit.object->kind != 0x17) {
                        t->hasLos = 0;
                    } else if ((TargetUnit *)hit.object->link->link != unit) {
                        t->hasLos = 0;
                    } else {
                        goto visible;
                    }
                } else {
                visible:
                    t->hasLos = 1;
                }
            } else {
                if (t->hasLos == 0) {
                    return;
                }
                set_yaw_transform(&m, t->x, 0.0f, t->z, t->heading);
                offset = D_80125FD0[type];
                offset.x *= scale;
                offset.y *= scale;
                offset.z *= scale;
                if (t->flags & 2) {
                    offset.x = -offset.x;
                }
                t->flags ^= 2;
                transform_point_3x4(&m, &offset.x, muzzle);
                start.x = muzzle[0];
                start.z = muzzle[2];
                end.x = unit->x;
                end.z = unit->z;
            }
            }
            if (t->hasLos == 0) {
                return;
            }
            func_800E3C18(unit, t);
            if (dist < 0x200) {
                s32 a;

                dx = unit->x - muzzle[0];
                dz = unit->z - muzzle[2];
                if ((dx != 0.0f) | (dz != 0.0f)) {
                    if (dx < 0.0f) {
                        a = -cosine_to_angle(dz / sqrtf(dx * dx + dz * dz));
                    } else {
                        a = cosine_to_angle(dz / sqrtf(dx * dx + dz * dz));
                    }
                } else {
                    a = 0;
                }
                aim = a;
            } else {
                aim = t->heading;
            }
            velocity[1] = sinf_u16(aim) * (f32)D_80125FC0[type];
            velocity[0] = cosf_u16(aim) * (f32)D_80125FC0[type];
            if (D_80126028[type] == 3) {
                spawn_beam_effect(muzzle, aim, t->owner.b[1], 0x12, owner->effectKind[type], 5, t, 0);
                start_sound_scaled_by_listener_distance(9, muzzle[0], muzzle[2]);
            } else {
                spawn_effect_kind_22(muzzle, velocity, D_80125FC0[type], aim, t->owner.b[1], owner->effectKind[type],
                                     D_80126028[type], (D_80126028[type] == 0) ? 0x10 : 0, t, 0);
                switch ((u32)type) {
                case 0:
                    start_sound_scaled_by_listener_distance(0x22, muzzle[0], muzzle[2]);
                    break;
                case 1:
                    start_sound_scaled_by_listener_distance(1, muzzle[0], muzzle[2]);
                    break;
                case 2:
                    start_sound_scaled_by_listener_distance(0x16, muzzle[0], muzzle[2]);
                    break;
                }
            }
            t->lastFire = D_801B4AA8;
            if (D_80126058[type] != 0) {
                u8 cycle = t->cycle;
                t->cycle = (!(next_random_u32() & 7) ? cycle + 2 : cycle + 1) % 5;
            }
        }
    } else if (t->aimTime != -1 && D_801B4AA8 - t->aimTime < 0x78) {
        u16 heading;
        u16 aimHeading;
        u16 fwd;
        u16 back;
        u16 dist;
        s32 delay;

        aimHeading = t->aimHeading;
        heading = t->heading;
        fwd = aimHeading - heading;
        back = heading - aimHeading;
        if (fwd < back) {
            t->heading = heading + ((fwd >= TURN_STEP(type)) ? TURN_STEP(type) : fwd);
        } else {
            t->heading = heading - ((back >= TURN_STEP(type)) ? TURN_STEP(type) : back);
        }
        dist = angle_distance(t->heading, t->aimHeading);
        delay = owner->fireDelay[type];
        if (D_80126058[type] != 0) {
            delay /= 4;
        }
        if (dist < 0x200) {
            TurretMatrix m;
            f32 muzzle[3];
            f32 velocity[2];
            Vec3 offset;
            PointZX start;
            u16 aim;

            f64 w = delay;
            f64 last = t->lastFire;
            f64 now = D_801B4AA8;
            if (!((t->flags & 4) ? (last + w * D_80126080[func_800A68AC(t->kind)] < now) : (last + w < now))) {
                return;
            }
            m = D_80072C24;
            set_yaw_transform(&m, t->x, 0.0f, t->z, t->heading);
            offset = D_80125FD0[type];
            offset.x *= scale;
            offset.y *= scale;
            offset.z *= scale;
            if (t->flags & 2) {
                offset.x = -offset.x;
            }
            t->flags ^= 2;
            transform_point_3x4(&m, &offset.x, muzzle);
            start.x = muzzle[0];
            start.z = muzzle[2];
            aim = t->heading;
            velocity[1] = sinf_u16(aim) * (f32)D_80125FC0[type];
            velocity[0] = cosf_u16(aim) * (f32)D_80125FC0[type];
            if (D_80126028[type] == 3) {
                spawn_beam_effect(muzzle, aim, t->owner.b[1], 0x12, owner->effectKind[type], 5, t, 0);
                start_sound_scaled_by_listener_distance(9, muzzle[0], muzzle[2]);
                if (next_random_u32() % D_80126048[type] == 0) {
                    t->aimTime = -1;
                }
            } else {
                spawn_effect_kind_22(muzzle, velocity, D_80125FC0[type], aim, t->owner.b[1], owner->effectKind[type],
                                     D_80126028[type], (D_80126028[type] == 0) ? 0x10 : 0, t, 0);
                switch ((u32)type) {
                case 0:
                    start_sound_scaled_by_listener_distance(0x22, muzzle[0], muzzle[2]);
                    break;
                case 1:
                    start_sound_scaled_by_listener_distance(1, muzzle[0], muzzle[2]);
                    break;
                case 2:
                    start_sound_scaled_by_listener_distance(0x16, muzzle[0], muzzle[2]);
                    break;
                }
                if (next_random_u32() % D_80126048[type] == 0) {
                    t->aimTime = -1;
                }
            }
            t->lastFire = D_801B4AA8;
        }
    }
}
