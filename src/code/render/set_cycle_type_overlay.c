#include "types.h"

#ifndef NULL
#define NULL 0
#endif

void *func_8007F060();

void set_cycle_type_overlay(s32 arg0) __asm__("func_800AB208");

void set_cycle_type_overlay(s32 arg0) {
    void *temp_a0;
    void *temp_v0;

    temp_v0 = func_8007F060();
    temp_a0 = (*(void **)((s8 *)(temp_v0) + (4)));
    (*(void **)((s8 *)(temp_v0) + (4))) = (void *) (temp_a0 + 8);
    (*(s32 *)((s8 *)(temp_a0) + (0))) = 0xBA000402;
    (*(s32 *)((s8 *)(temp_a0) + (4))) = arg0;
}
