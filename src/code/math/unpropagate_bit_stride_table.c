#include "types.h"

typedef struct {
    s32 start;
    s32 stride;
} BitStrideEntry;

extern u8 gBitStrideTable[] __asm__("D_8013578C");

u32 unpropagate_bit_stride_table(u32 value) __asm__("func_800DD2A8");

u32 unpropagate_bit_stride_table(u32 value)
{
    u32 one = 1;
    s32 offset;
    u32 bit;
    s32 stride;
    u32 result;

    for (offset = 15 * sizeof(BitStrideEntry); offset >= 0; offset -= sizeof(BitStrideEntry)) {
        result = value;
        bit = ((BitStrideEntry *)(gBitStrideTable + offset))->start;
        stride = ((BitStrideEntry *)(gBitStrideTable + offset))->stride;
        if ((result >> bit) & 1) {
            for (bit += stride; bit < 32; bit += stride) {
                result ^= one << bit;
            }
        }
        value = result;
    }
    return value;
}
