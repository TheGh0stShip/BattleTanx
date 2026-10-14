#include "types.h"

u8 byte_mask_intersects(u32 value, u32 mask) __asm__("func_800E1A08");

u8 byte_mask_intersects(u32 value, u32 mask)
{
    return value & mask;
}
