#include "types.h"

typedef struct TimedStateEffect {
    u8 pad00[0x10];
    s32 state;
    u8 pad14[0x10];
    s32 expireTick;
} TimedStateEffect;

#define TIMED_EFFECT_ARMED 2

extern s32 gGameTicks __asm__("D_801B4AA8");
extern void dispatch_record_byte_0c(TimedStateEffect *effect) __asm__("func_800A70BC");

void expire_effect_after_timer(TimedStateEffect *effect, s32 *state) __asm__("func_800A6900");

void expire_effect_after_timer(TimedStateEffect *effect, s32 *state)
{
    if (effect->state == TIMED_EFFECT_ARMED) {
        if (gGameTicks > effect->expireTick) {
            dispatch_record_byte_0c(effect);
            *state = 1;
        }
    } else {
        *state = 1;
    }
}
