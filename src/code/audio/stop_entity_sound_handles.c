#include "types.h"

#ifndef NULL
#define NULL 0
#endif

s32 func_800798C0(s32);

void stop_entity_sound_handles(void *arg0) __asm__("func_80097B04");

void stop_entity_sound_handles(void *arg0) {
    s32 temp_a0;
    s32 temp_a0_2;
    s32 temp_a0_3;

    temp_a0 = (*(s32 *)((s8 *)(arg0) + (0x458)));
    if (temp_a0 != -1) {
        func_800798C0(temp_a0);
        (*(s32 *)((s8 *)(arg0) + (0x458))) = -1;
    }
    temp_a0_2 = (*(s32 *)((s8 *)(arg0) + (0x45C)));
    if (temp_a0_2 != -1) {
        func_800798C0(temp_a0_2);
        (*(s32 *)((s8 *)(arg0) + (0x45C))) = -1;
    }
    temp_a0_3 = (*(s32 *)((s8 *)(arg0) + (0x4F0)));
    if (temp_a0_3 != -1) {
        func_800798C0(temp_a0_3);
        (*(s32 *)((s8 *)(arg0) + (0x4F0))) = -1;
    }
}
