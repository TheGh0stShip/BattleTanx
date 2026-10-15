#include "types.h"

typedef struct SlotHeadingEffect {
    u8 pad00[0xC];
    u8 flags;
    u8 pad0D[0x13];
    s32 slot;
    u8 pad24[0x10];
    s16 heading;
} SlotHeadingEffect;

typedef struct SessionSlot {
    u8 state;
    u8 pad01[0x47];
    f32 x;
    f32 z;
    u8 pad50[0x8];
} SessionSlot;

typedef struct HeadingSession {
    u8 pad000[0x568];
    SessionSlot *slots;
} HeadingSession;

typedef struct HeadingPos {
    f32 x;
    f32 z;
} HeadingPos;

extern float sqrtf(float);
extern HeadingSession *get_spawn_session(void) __asm__("func_800821C0");
extern s32 radians_to_angle(f32 radians) __asm__("func_800F3BE4");
extern void release_effect(SlotHeadingEffect *effect) __asm__("func_8008B89C");

static inline void clear_slot_state_nibble(SlotHeadingEffect *effect) {
    SessionSlot *slot = &get_spawn_session()->slots[effect->slot];
    u8 state = slot->state;

    if ((state & 0xF) == 0xF) {
        slot->state = state & 0xF0;
    }
}

void face_slot_effect_away_from_point(SlotHeadingEffect *effect, s32 arg1, HeadingPos *pos) __asm__("func_800F0B60");

void face_slot_effect_away_from_point(SlotHeadingEffect *effect, s32 arg1, HeadingPos *pos)
{
    SessionSlot *slot;
    f32 dz;
    f32 dx;

    if (effect->flags & 4) {
        return;
    }
    effect->flags |= 3;
    slot = &get_spawn_session()->slots[effect->slot];
    dz = pos->z - slot->z;
    dx = pos->x - slot->x;
    if ((dz != 0.0f) | (dx != 0.0f)) {
        effect->flags |= 8;
        if (-dz < 0.0f) {
            effect->heading = -radians_to_angle(-dx / sqrtf(dz * dz + dx * dx));
        } else {
            effect->heading = radians_to_angle(-dx / sqrtf(dz * dz + dx * dx));
        }
    }
    clear_slot_state_nibble(effect);
    release_effect(effect);
}
