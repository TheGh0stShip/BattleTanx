#include "types.h"

#ifndef NULL
#define NULL 0
#endif

s32 func_8007F204(s32);
s32 func_801219B0(s32);
s32 func_801222F0(s32);

void scheduler_swap_framebuffer(void *arg0) __asm__("func_80079530");

void scheduler_swap_framebuffer(void *arg0) {
    s32 temp_v0;

    if ((u16) (*(u16 *)((s8 *)(arg0) + (0x1F0))) >= (u16) (*(u16 *)((s8 *)(arg0) + (0x1EC)))) {
        temp_v0 = func_8007F204(1);
        if (temp_v0 != 0) {
            if ((*(u16 *)((s8 *)(arg0) + (0x1F2))) != 0) {
                func_801219B0(0);
                (*(u16 *)((s8 *)(arg0) + (0x1F2))) = 0U;
            }
            func_801222F0(temp_v0);
            (*(u16 *)((s8 *)(arg0) + (0x1F0))) = 0U;
        }
    }
}
