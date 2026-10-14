#include "types.h"

s32 func_800E3470(void *value)
{
    return *(u8 *)((u8 *)value + 0x350) == 1;
}
