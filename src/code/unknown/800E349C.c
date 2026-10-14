#include "types.h"

void func_800E349C(void *value)
{
    *(u32 *)((u8 *)value + 0x9C) = 0;
    *(u32 *)((u8 *)value + 0xA0) = 0;
    *(u16 *)((u8 *)value + 0x344) = 0;
    *(u8 *)((u8 *)value + 0x34A) = 0;
    *(u8 *)((u8 *)value + 0x348) = 0;
}
