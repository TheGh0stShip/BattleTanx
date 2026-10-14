#include "types.h"

typedef struct TimedSound {
    u8 pad00[0x12];
    u16 elapsed;
} TimedSound;

s32 sound_duration_elapsed(TimedSound *sound, u32 duration) __asm__("func_800EDA98");

s32 sound_duration_elapsed(TimedSound *sound, u32 duration)
{
    return sound->elapsed >= (duration >> 16);
}
