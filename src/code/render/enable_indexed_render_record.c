#include "types.h"

extern u8 *D_801C9170;

void enable_indexed_render_record(s32 index) __asm__("func_80085DE4");

void enable_indexed_render_record(s32 index)
{
    register s32 offset __asm__("$2");

    offset = -1;
    if (index == offset) {
        return;
    }
    offset = index << 1;
    {
        u8 *records = *(u8 **)(D_801C9170 + 0x570);
        offset += index;
        offset <<= 2;
        records[offset] = 1;
    }
}
