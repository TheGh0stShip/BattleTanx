#include "types.h"

#ifndef NULL
#define NULL 0
#endif

void **func_8007F060();

void set_env_color_main(void *arg0) __asm__("func_800A9E10");

void set_env_color_main(void *arg0) {
    void **temp_v0;
    void *temp_a1;

    temp_v0 = func_8007F060();
    temp_a1 = *temp_v0;
    *temp_v0 = temp_a1 + 8;
    (*(s32 *)((s8 *)(temp_a1) + (0))) = 0xFB000000;
    (*(s32 *)((s8 *)(temp_a1) + (4))) = (s32) (((*(u8 *)((s8 *)(arg0) + (0))) << 0x18) | ((*(u8 *)((s8 *)(arg0) + (1))) << 0x10) | ((*(u8 *)((s8 *)(arg0) + (2))) << 8) | (*(u8 *)((s8 *)(arg0) + (3))));
}
