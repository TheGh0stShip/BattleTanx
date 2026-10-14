#include "types.h"

#ifndef NULL
#define NULL 0
#endif

extern void *D_801257D0;

s32 push_segment_matrix_command(s32 arg0) __asm__("func_8007EB04");

s32 push_segment_matrix_command(s32 arg0) {
    void *temp_a1;
    void *temp_a2;

    temp_a2 = (*(void **)((s8 *)(D_801257D0) + (0xDC)));
    (*(void **)((s8 *)(D_801257D0) + (0xDC))) = (void *) (temp_a2 + 8);
    temp_a1 = D_801257D0 + (((*(u16 *)((s8 *)(D_801257D0) + (0xD0))) * 0x18) + 0x90);
    (*(s32 *)((s8 *)(temp_a2) + (0))) = (s32) (((arg0 & 0xFF) << 0x10) | 0x01000040);
    (*(s32 *)((s8 *)(temp_a2) + (4))) = (s32) ((*(s32 *)((s8 *)(temp_a1) + (0x14))) - 0x80000000);
    return (*(s32 *)((s8 *)(temp_a1) + (0x14)));
}
