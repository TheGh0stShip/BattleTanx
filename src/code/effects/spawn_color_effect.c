#include "types.h"

#ifndef NULL
#define NULL 0
#endif

void *func_8008AD10(s32, s32, s32);

void spawn_color_effect(s8 arg0, s8 arg1, s8 arg2, s8 arg3, u8 arg4, u8 arg5, s32 arg6, s32 arg7) __asm__("func_800F3014");

void spawn_color_effect(s8 arg0, s8 arg1, s8 arg2, s8 arg3, u8 arg4, u8 arg5, s32 arg6, s32 arg7) {
    void *temp_v0;

    temp_v0 = func_8008AD10(1, 0x20, 0x20);
    if (temp_v0 != NULL) {
        (*(s8 *)((s8 *)(temp_v0) + (0xC))) = arg0;
        (*(s8 *)((s8 *)(temp_v0) + (0xD))) = arg1;
        (*(s8 *)((s8 *)(temp_v0) + (0xE))) = arg2;
        (*(s8 *)((s8 *)(temp_v0) + (0xF))) = arg3;
        (*(u8 *)((s8 *)(temp_v0) + (0x10))) = arg4;
        (*(u8 *)((s8 *)(temp_v0) + (0x11))) = arg5;
        (*(s32 *)((s8 *)(temp_v0) + (0x14))) = arg6;
        (*(s32 *)((s8 *)(temp_v0) + (0x18))) = 0;
        (*(s32 *)((s8 *)(temp_v0) + (0x1C))) = arg7;
    }
}
