#include "types.h"

extern u8 D_801262D8[];

void *get_record_72(s32 index) __asm__("func_800A68C0");

void *get_record_72(s32 index)
{
    return D_801262D8 + index * 72;
}
