#include "types.h"

#ifndef NULL
#define NULL 0
#endif

void *func_800821C0();

void clear_player_slot_nibble(void *arg0) __asm__("func_800F0234");

void clear_player_slot_nibble(void *arg0) {
    u8 *temp_a1;
    u8 temp_a0;

    temp_a1 = (*(s32 *)((s8 *)(func_800821C0()) + (0x568))) + ((*(s32 *)((s8 *)(arg0) + (0x20))) * 0x58);
    temp_a0 = *temp_a1;
    if ((temp_a0 & 0xF) == 0xF) {
        *temp_a1 = temp_a0 & 0xF0;
    }
}
