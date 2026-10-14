#include "types.h"

#ifndef NULL
#define NULL 0
#endif

void *func_8007F060();

void emit_triangle_main(s32 arg0, s32 arg1, s32 arg2) __asm__("func_800AA280");

void emit_triangle_main(s32 arg0, s32 arg1, s32 arg2) {
    void *temp_a0;
    void *temp_v0;
    void *temp_v1;

    temp_v0 = func_8007F060();
    if ((*(u16 *)((s8 *)(temp_v0) + (0x14))) == 0) {
        temp_v1 = (*(void **)((s8 *)(temp_v0) + (0)));
        (*(void **)((s8 *)(temp_v0) + (0))) = (void *) (temp_v1 + 8);
        (*(s32 *)((s8 *)(temp_v1) + (0))) = 0xB6000000;
        (*(s32 *)((s8 *)(temp_v1) + (4))) = 0x3000;
        temp_a0 = (*(void **)((s8 *)(temp_v0) + (0)));
        (*(void **)((s8 *)(temp_v0) + (0))) = (void *) (temp_a0 + 8);
        (*(s32 *)((s8 *)(temp_a0) + (0))) = 0xBF000000;
        (*(s32 *)((s8 *)(temp_a0) + (4))) = (s32) ((((arg0 * 2) & 0xFE) << 0x10) | ((arg1 << 9) & 0xFE00) | ((arg2 * 2) & 0xFE));
    }
}
