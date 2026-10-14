#include "types.h"

void debug_store_byte(u32 address, u8 value)
{
    u32 shift;
    u32 mask;
    u32 *aligned;

    shift = (~address & 3) << 3;
    aligned = (u32 *)(address & ~3);
    mask = 0xFF << shift;
    *aligned = (*aligned & ~mask) | ((value & 0xFF) << shift);
}
