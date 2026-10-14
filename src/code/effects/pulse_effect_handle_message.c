#include "types.h"

typedef struct PulseEffect {
    u8 pad00[0xC];
    u8 flags;
    u8 frameCount;
    u8 frame;
    u8 pad0F[0x5];
    s32 value14;
    s32 lastTime;
    s16 shakeTimer;
} PulseEffect;

typedef struct PulseTarget {
    u8 pad000[0x3D0];
    f32 value3D0;
    f32 value3D4;
} PulseTarget;

typedef struct PulseEffectMessage {
    u8 pad00[0x8];
    u32 kind;
    PulseTarget *target;
} PulseEffectMessage;

extern s32 D_801B4AA0;
extern void release_effect(PulseEffect *effect) __asm__("func_8008B89C");
extern void func_80106CCC(s32, s32);

void pulse_effect_handle_message(PulseEffect *effect, PulseEffectMessage *message, s32 arg2,
                                 s32 *result) __asm__("func_80093590");

void pulse_effect_handle_message(PulseEffect *effect, PulseEffectMessage *message, s32 arg2,
                                 s32 *result)
{
    PulseTarget *target;
    s32 now;
    s32 flags;
    s32 count;
    s32 frame;
    s32 last;

    switch (message->kind) {
    case 2:
    case 12:
    case 22:
    case 34:
    case 44:
        flags = effect->flags;
        count = effect->frameCount;
        frame = effect->frame;
        if (flags & 1) {
            last = count - 2;
        } else {
            last = count - 1;
        }
        if (frame == last) {
            break;
        }
        if (effect->flags & 1) {
            if (!(effect->flags & 4)) {
                effect->flags |= 2;
            }
        } else {
            effect->flags |= 4;
        }
        release_effect(effect);
        *result = 0;
        return;
    case 0:
        if (effect->shakeTimer != 0) {
            target = message->target;
            target->value3D0 -= 6.0;
            if (effect->shakeTimer & 1) {
                target->value3D4 -= 2.0f;
            } else {
                target->value3D4 += 2.0f;
            }
            if (--effect->shakeTimer == 0) {
                func_80106CCC(effect->value14, 0x10);
            }
            *result = 0;
            return;
        }
        if (effect->frame == 0) {
            release_effect(effect);
            effect->flags |= 4;
            now = D_801B4AA0;
            if (effect->lastTime + 10 >= now) {
                break;
            }
            *result = 5;
        } else {
            now = D_801B4AA0;
            if (effect->lastTime + 10 >= now) {
                break;
            }
            *result = 4;
        }
        effect->lastTime = now;
        return;
        break;
    }
    *result = 1;
}
