#include "types.h"

#ifndef NULL
#define NULL 0
#endif

s32 ai_unit_in_expected_state(void *arg0) __asm__("func_800E3BC0");

s32 ai_unit_in_expected_state(void *arg0) {
    u32 temp_v1;

    temp_v1 = (*(u32 *)((s8 *)(arg0) + (0xB4)));
    if (temp_v1 == 2) {
        goto block_4;
    }
    if (temp_v1 >= 3U) {
        goto block_6;
    }
    if (temp_v1 == 1) {
        goto block_5;
    }
    return 0;
block_4:
    return (*(s32 *)((s8 *)(arg0) + (0x9C))) == 6;
block_5:
    return (*(s32 *)((s8 *)(arg0) + (0x9C))) == 5;
block_6:
    return 0;
}
