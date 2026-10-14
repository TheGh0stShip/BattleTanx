#include "types.h"

extern u8 func_80096920(s32 group, s32 index);

s32 query_primary_mode_active(void) __asm__("func_800C5B64");

s32 query_primary_mode_active(void)
{
    return func_80096920(0, 0) != 0;
}
