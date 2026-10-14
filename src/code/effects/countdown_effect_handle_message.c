#include "types.h"

typedef struct CountdownSlot {
    u8 flags;
    u8 pad01[0x57];
} CountdownSlot;

typedef struct CountdownSession {
    u8 pad000[0x568];
    CountdownSlot *slots;
} CountdownSession;

typedef struct CountdownEffect {
    u8 pad00[0xC];
    f32 z;
    f32 x;
    u16 angle;
    u16 value16;
    s16 value18;
    u8 pad1A[0x2];
    s32 record;
    s32 slot;
    u8 pad24[0x2];
    s16 sound;
    u8 pad28[0x2];
    s16 timer;
    u8 pad2C;
    u8 flags;
} CountdownEffect;

typedef struct CountdownTarget {
    u8 pad000[0x3B4];
    f32 value3B4;
} CountdownTarget;

typedef struct CountdownMessage {
    u8 pad00[0x8];
    u32 kind;
    CountdownTarget *target;
} CountdownMessage;

typedef struct CountdownSource {
    u8 pad00[0xC];
    u16 value0C;
} CountdownSource;

extern f32 D_80074C20;
extern f32 D_80074C24;

extern CountdownSession *get_spawn_session(void) __asm__("func_800821C0");
extern s32 start_sound_scaled_by_listener_distance(s32 soundId, f32 x, f32 z) __asm__("func_80085B4C");
extern void release_effect(CountdownEffect *effect) __asm__("func_8008B89C");
extern void func_800905D8(s32 sound, f32 *pos, s32 a2, u16 angle, s32 a4, s32 a5, s32 a6);
extern void clear_record_halfword_flags(s32 index, u16 flags) __asm__("func_80106CCC");
extern void func_80107170(s32 motion);

void countdown_effect_handle_message(CountdownEffect *effect, CountdownMessage *message, CountdownSource *source,
                                     s32 *result) __asm__("func_800EFAD8");

void countdown_effect_handle_message(CountdownEffect *effect, CountdownMessage *message, CountdownSource *source,
                                     s32 *result)
{
    CountdownSession *session;
    f32 pos[3];
    f32 scaled;
    s32 timer;
    s32 remaining;
    s16 clamped;

    if (message->kind == 0) {
        timer = effect->timer;
        if (timer != 0) {
            scaled = message->target->value3B4 * D_80074C20;
            if (scaled > D_80074C24) {
                remaining = timer - (s16)scaled;
            } else {
                remaining = timer - 1;
            }
            clamped = remaining;
            if (clamped < 0) {
                clamped = 0;
            }
            effect->timer = clamped;
            if (effect->timer == 0) {
                clear_record_halfword_flags(effect->record, 0x10);
            }
            *result = 0;
            return;
        }
        session = get_spawn_session();
        start_sound_scaled_by_listener_distance(7, effect->x, effect->z);
        release_effect(effect);
        if (effect->flags & 1) {
            pos[0] = effect->x;
            pos[1] = 0.0f;
            pos[2] = effect->z;
            func_800905D8(effect->sound, pos, 0, effect->angle, 0, 0, 8);
            func_800905D8(effect->sound, pos, 0, effect->angle + 0x2000, 0, 0, 8);
        }
        effect->value18 = 1;
        effect->value16 = source->value0C;
        session->slots[effect->slot].flags &= 0xF;
        if (effect->record >= 0) {
            func_80107170(effect->record);
            effect->record = -1;
        }
        *result = 4;
    } else {
        *result = 1;
    }
}
