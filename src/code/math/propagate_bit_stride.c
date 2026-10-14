#include "types.h"

u32 propagate_bit_stride(u32 value, s32 sourceBit, s32 stride)
    __asm__("func_800DD200");

u32 propagate_bit_stride(u32 value, s32 sourceBit, s32 stride)
{
    u32 bit;
    u32 nextBit;

    bit = value;
    if ((bit >> sourceBit) & 1) {
        nextBit = sourceBit + stride;
        if (nextBit < 32U) {
            do {
                bit ^= 1 << nextBit;
                nextBit += stride;
            } while (nextBit < 32U);
        }
    }
    return bit;
}
