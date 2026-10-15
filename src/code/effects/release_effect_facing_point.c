#include "types.h"

typedef struct FacingEffect {
    u8 pad00[0xC];
    u8 flags;
    u8 pad0D[0x13];
    s32 slot;
    u8 pad24[0x10];
    s16 heading;
} FacingEffect;

typedef struct SpawnSlot {
    u8 flags;
    u8 pad01[0x47];
    f32 x;
    f32 z;
    u8 pad50[0x8];
} SpawnSlot;

typedef struct SpawnSession {
    u8 pad000[0x568];
    SpawnSlot *slots;
} SpawnSession;

typedef struct FacingPos {
    f32 x;
    f32 z;
} FacingPos;

extern float sqrtf(float);
extern SpawnSession *get_spawn_session(void) __asm__("func_800821C0");
extern void release_effect(FacingEffect *effect) __asm__("func_8008B89C");
extern s32 radians_to_angle(f32 radians) __asm__("func_800F3BE4");

void release_effect_facing_point(FacingEffect *effect, s32 arg1, FacingPos *pos) __asm__("func_800F09D0");

void release_effect_facing_point(FacingEffect *effect, s32 arg1, FacingPos *pos)
{
    SpawnSlot *anchor;
    SpawnSlot *slot;
    f32 dz;
    f32 dx;

    if (effect->flags & 4) {
        return;
    }
    effect->flags |= 3;
    anchor = &get_spawn_session()->slots[effect->slot];
    dz = pos->z - anchor->z;
    dx = pos->x - anchor->x;
    if ((dz != 0.0f) | (dx != 0.0f)) {
        effect->flags |= 8;
        if (-dz < 0.0f) {
            effect->heading = -radians_to_angle(-dx / sqrtf(dz * dz + dx * dx));
        } else {
            effect->heading = radians_to_angle(-dx / sqrtf(dz * dz + dx * dx));
        }
    }
    slot = &get_spawn_session()->slots[effect->slot];
    if ((slot->flags & 0xF) == 0xF) {
        slot->flags &= 0xF0;
    }
    release_effect(effect);
}
