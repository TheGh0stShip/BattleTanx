#include "types.h"

typedef struct TimedEventOwner {
    u8 pad000[0x1A6];
    u8 disabled;
    u8 pad1A7[0x71];
    s32 activeEvent;
    s32 activeUntil;
    u8 pad220[0x40];
    s32 lastStart[1];
} TimedEventOwner;

extern s32 find_sound_instance(s32 soundId, s32 index) __asm__("func_800796F0");
extern f32 D_80072DE4;
extern s16 D_801260A8[];
extern s32 gGameTicks __asm__("D_801B4AA8");

void start_cooldown_timed_event(TimedEventOwner *owner, s32 event, f32 duration) __asm__("func_800A51E8");

void start_cooldown_timed_event(TimedEventOwner *owner, s32 event, f32 duration)
{
    if (owner->disabled == 0) {
        if (owner->lastStart[event] == 0
            || owner->lastStart[event] + D_801260A8[event] < gGameTicks) {
            if (event == 1) {
                find_sound_instance(0x2C, 0);
            }
            owner->activeEvent = event;
            owner->activeUntil = gGameTicks + (s32)(duration * D_80072DE4);
            owner->lastStart[event] = gGameTicks;
        }
    }
}
