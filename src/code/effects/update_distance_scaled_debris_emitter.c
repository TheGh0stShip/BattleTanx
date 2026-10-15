#include "types.h"

typedef struct DebrisEmitter {
    u8 pad00[0x12];
    u16 entity;
    s32 modelSlot;
    u16 partCount;
    u8 pad1A[0x2];
    f32 x;
    f32 z;
    u8 pad24[0x8];
    s16 timer;
} DebrisEmitter;

typedef struct DebrisTarget {
    f32 x;
    f32 z;
    s32 elapsed;
} DebrisTarget;

typedef struct DebrisEntity {
    u8 pad000[0x1BF];
    u8 team;
} DebrisEntity;

typedef struct DebrisOrigin {
    f32 z;
    s32 y;
    f32 x;
} DebrisOrigin;

extern float sqrtf(float);
extern s32 radians_to_angle(f32 radians) __asm__("func_800F3BE4");
extern DebrisEntity *get_entity_record(u16 index) __asm__("func_800A6688");
extern void spawn_group_part_debris(s16 model, DebrisOrigin *origin, s32 a2, u16 count, s32 a4, u16 angle, s32 team)
    __asm__("func_80090428");
extern s32 D_80125FB0[];
extern s16 D_802D5A30[];

static inline f32 xz_length(f32 dz, f32 dx) {
    return sqrtf(dz * dz + dx * dx);
}

void update_distance_scaled_debris_emitter(DebrisEmitter *emitter, s32 arg1, DebrisTarget *target)
    __asm__("func_800A2A44");

void update_distance_scaled_debris_emitter(DebrisEmitter *emitter, s32 arg1, DebrisTarget *target) {
    DebrisOrigin origin;
    f32 dz;
    f32 dx;
    f32 dist;
    s32 rate;
    s32 angle;

    dz = target->z - emitter->z;
    dx = target->x - emitter->x;
    dist = sqrtf(dz * dz + dx * dx);
    if (4000.0f < dist) {
        rate = 50;
    } else {
        rate = (s32)((1.0f - dist / 4000.0f) * 50.0f) + 50;
    }
    emitter->timer -= rate;
    if (emitter->timer > 0) {
        return;
    }
    emitter->timer = 0;
    if ((dz != 0.0f) | (dx != 0.0f)) {
        if (-dz < 0.0f) {
            angle = -radians_to_angle(-dx / sqrtf(dz * dz + dx * dx));
        } else {
            angle = radians_to_angle(-dx / sqrtf(dz * dz + dx * dx));
        }
    } else {
        angle = 0;
    }
    origin.z = emitter->z;
    origin.y = 0;
    origin.x = emitter->x;
    spawn_group_part_debris(D_802D5A30[D_80125FB0[emitter->modelSlot]], &origin, 0, emitter->partCount, 0, angle,
                            get_entity_record(emitter->entity)->team);
}
