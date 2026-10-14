#include "types.h"

extern u8 gRenderBytes[5] __asm__("D_801257F0");
extern s8 gIndexedRenderBytes[][4] __asm__("D_801257E0");
extern u8 gRenderScratchBuffer[] __asm__("D_801B6C20");

void set_render_byte_settings(u8 value0, u8 value1, u8 value2, u8 value3, u8 value4)
    __asm__("func_8008054C");
void set_indexed_render_bytes(s8 value0, s8 value1, s8 value2, s8 value3, s32 index)
    __asm__("func_80080580");
u8 *get_render_scratch_buffer(void) __asm__("func_800805C0");

void set_render_byte_settings(u8 value0, u8 value1, u8 value2, u8 value3, u8 value4)
{
    gRenderBytes[0] = value0;
    gRenderBytes[1] = value1;
    gRenderBytes[2] = value2;
    gRenderBytes[3] = value3;
    gRenderBytes[4] = value4;
}

void set_indexed_render_bytes(s8 value0, s8 value1, s8 value2, s8 value3, s32 index)
{
    gIndexedRenderBytes[index][0] = value0;
    gIndexedRenderBytes[index][1] = value1;
    gIndexedRenderBytes[index][2] = value2;
    gIndexedRenderBytes[index][3] = value3;
}

u8 *get_render_scratch_buffer(void)
{
    return gRenderScratchBuffer;
}
