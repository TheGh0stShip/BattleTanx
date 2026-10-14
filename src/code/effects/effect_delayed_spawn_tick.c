#include "types.h"

typedef struct DelayedSpawn {
    u8 pad00[0xC];
    u8 spawnArgs[0xC];
    u16 value18;
    u8 value1A;
    u8 pad1B;
    s16 value1C;
    u8 pad1E[0x2];
    s32 value20;
    s32 value24;
    s32 value28;
    u8 delay;
} DelayedSpawn;

extern void func_800F0FD8(void *spawnArgs, u16 arg1, u8 arg2, s16 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7);

void effect_delayed_spawn_tick(DelayedSpawn *spawn, s32 *state) __asm__("func_800F1670");

void effect_delayed_spawn_tick(DelayedSpawn *spawn, s32 *state)
{
    if (spawn->delay == 0) {
        func_800F0FD8(spawn->spawnArgs, spawn->value18, spawn->value1A, spawn->value1C, spawn->value20,
                      spawn->value24, spawn->value28, 1);
        *state = 2;
        return;
    }
    spawn->delay--;
}
