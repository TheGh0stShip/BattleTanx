#include "types.h"

#ifndef NULL
#define NULL 0
#endif

void *func_8007F060();

void append_textured_vertex(void *arg0) __asm__("func_800AA098");

void append_textured_vertex(void *arg0) {
    u16 temp_a2;
    void *temp_v0;
    void *temp_v1;

    temp_v0 = func_8007F060();
    temp_a2 = (*(u16 *)((s8 *)(temp_v0) + (0x2C)));
    if (temp_a2 == 0x20) {
        (*(s16 *)((s8 *)(temp_v0) + (0x14))) = 1;
        return;
    }
    temp_v1 = (*(s32 *)((s8 *)(temp_v0) + (0xC))) + (temp_a2 * 0x10);
    (*(s16 *)((s8 *)(temp_v1) + (0))) = (*(f32 *)((s8 *)(arg0) + (4)));
    (*(s16 *)((s8 *)(temp_v1) + (2))) = (*(f32 *)((s8 *)(arg0) + (8)));
    (*(s16 *)((s8 *)(temp_v1) + (4))) = (*(f32 *)((s8 *)(arg0) + (0xC)));
    (*(s16 *)((s8 *)(temp_v1) + (8))) = (*(u16 *)((s8 *)(arg0) + (0))) << 6;
    (*(s16 *)((s8 *)(temp_v1) + (0xA))) = (*(u16 *)((s8 *)(arg0) + (2))) << 6;
    (*(u8 *)((s8 *)(temp_v1) + (0xC))) = (*(u8 *)((s8 *)(temp_v0) + (0x1E)));
    (*(u8 *)((s8 *)(temp_v1) + (0xD))) = (*(u8 *)((s8 *)(temp_v0) + (0x1F)));
    (*(u8 *)((s8 *)(temp_v1) + (0xE))) = (*(u8 *)((s8 *)(temp_v0) + (0x20)));
    (*(u8 *)((s8 *)(temp_v1) + (0xF))) = (*(u8 *)((s8 *)(temp_v0) + (0x21)));
    (*(u16 *)((s8 *)(temp_v0) + (0x18))) = (*(u16 *)((s8 *)(temp_v0) + (0x18))) + 1;
    (*(u16 *)((s8 *)(temp_v0) + (0x2C))) = (*(u16 *)((s8 *)(temp_v0) + (0x2C))) + 1;
}
