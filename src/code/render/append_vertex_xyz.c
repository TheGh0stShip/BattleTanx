#include "types.h"

#ifndef NULL
#define NULL 0
#endif

void *func_8007F060();

void append_vertex_xyz(f32 arg0, f32 arg1, f32 arg2) __asm__("func_800A9FC4");

void append_vertex_xyz(f32 arg0, f32 arg1, f32 arg2) {
    u16 temp_t0;
    void *temp_v0;
    void *temp_v0_2;

    temp_v0 = func_8007F060();
    temp_t0 = (*(u16 *)((s8 *)(temp_v0) + (0x2C)));
    if (temp_t0 == 0x20) {
        (*(s16 *)((s8 *)(temp_v0) + (0x14))) = 1;
        return;
    }
    temp_v0_2 = (*(s32 *)((s8 *)(temp_v0) + (0xC))) + (temp_t0 * 0x10);
    (*(s16 *)((s8 *)(temp_v0_2) + (0))) = arg0;
    (*(s16 *)((s8 *)(temp_v0_2) + (2))) = arg1;
    (*(s16 *)((s8 *)(temp_v0_2) + (4))) = arg2;
    (*(u16 *)((s8 *)(temp_v0_2) + (8))) = (*(u16 *)((s8 *)(temp_v0) + (0x1A)));
    (*(u16 *)((s8 *)(temp_v0_2) + (0xA))) = (*(u16 *)((s8 *)(temp_v0) + (0x1C)));
    (*(u8 *)((s8 *)(temp_v0_2) + (0xC))) = (*(u8 *)((s8 *)(temp_v0) + (0x1E)));
    (*(u8 *)((s8 *)(temp_v0_2) + (0xD))) = (*(u8 *)((s8 *)(temp_v0) + (0x1F)));
    (*(u8 *)((s8 *)(temp_v0_2) + (0xE))) = (*(u8 *)((s8 *)(temp_v0) + (0x20)));
    (*(u8 *)((s8 *)(temp_v0_2) + (0xF))) = (*(u8 *)((s8 *)(temp_v0) + (0x21)));
    (*(u16 *)((s8 *)(temp_v0) + (0x18))) = (*(u16 *)((s8 *)(temp_v0) + (0x18))) + 1;
    (*(u16 *)((s8 *)(temp_v0) + (0x2C))) = (*(u16 *)((s8 *)(temp_v0) + (0x2C))) + 1;
}
