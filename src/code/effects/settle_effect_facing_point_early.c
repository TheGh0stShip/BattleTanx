#include "types.h"

typedef struct SettlingEffect {
    u8 pad00[0xC];
    f32 x;
    f32 z;
    u8 pad14[0x2];
    s16 heading;
    u16 settled;
    u8 pad1A[0x2];
    s32 motion;
    s32 slot;
} SettlingEffect;

typedef struct SpawnSlot {
    u8 flags;
    u8 pad01[0x57];
} SpawnSlot;

typedef struct SpawnSession {
    u8 pad000[0x568];
    SpawnSlot *slots;
} SpawnSession;

typedef struct SettlePos {
    f32 x;
    f32 z;
} SettlePos;

extern float sqrtf(float);
extern SpawnSession *get_spawn_session(void) __asm__("func_800821C0");
extern void release_effect(SettlingEffect *effect) __asm__("func_8008B89C");
extern s32 radians_to_angle(f32 radians) __asm__("func_800F3BE4");
extern void func_80107170(s32 motion);

void settle_effect_facing_point_early(SettlingEffect *effect, s32 arg1, SettlePos *pos) __asm__("func_800EFCD0");

void settle_effect_facing_point_early(SettlingEffect *effect, s32 arg1, SettlePos *pos) {
    SpawnSession *session;
    f32 dz;
    f32 dx;

    if (effect->settled != 0) {
        return;
    }
    session = get_spawn_session();
    release_effect(effect);
    effect->settled = 1;
    dz = pos->z - effect->z;
    dx = pos->x - effect->x;
    if ((dz != 0.0f) | (dx != 0.0f)) {
        if (-dz < 0.0f) {
            effect->heading = -radians_to_angle(-dx / sqrtf(dz * dz + dx * dx));
        } else {
            effect->heading = radians_to_angle(-dx / sqrtf(dz * dz + dx * dx));
        }
    } else {
        effect->heading = 0;
    }
    session->slots[effect->slot].flags &= 0xF;
    if (effect->motion >= 0) {
        func_80107170(effect->motion);
        effect->motion = -1;
    }
}
