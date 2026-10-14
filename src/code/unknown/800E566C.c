#include "types.h"

void func_800E566C(void *value)
{
    *(u8 *)((u8 *)value + 4) = 0;
    *(u8 *)((u8 *)value + 5) = 0;
    *(u8 *)((u8 *)value + 6) = 0;
    *(u8 *)((u8 *)value + 7) = 0;
    *(u32 *)((u8 *)value + 8) = 0;
    *(u8 *)((u8 *)value + 3) = 0;
}
