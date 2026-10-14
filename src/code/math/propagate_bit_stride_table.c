#include "types.h"

typedef struct {
    s32 start;
    s32 stride;
} BitStrideEntry;

extern BitStrideEntry gBitStrideTable[] __asm__("D_8013578C");

u32 propagate_bit_stride_table(u32 value) __asm__("func_800DD244");

u32 propagate_bit_stride_table(u32 value)
{
    u32 bit;
    s32 i;
    s32 start;
    s32 stride;

    for (i = 0; i < 16; i++) {
        start = gBitStrideTable[i].start;
        stride = gBitStrideTable[i].stride;
        if ((value >> start) & 1) {
            for (bit = start + stride; bit < 32; bit += stride) {
                value ^= 1 << bit;
            }
        }
    }
    return value;
}
