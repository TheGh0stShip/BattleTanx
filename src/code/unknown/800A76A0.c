#include "types.h"

void func_800A76A0(void *value, f32 *vector)
{
    *(f32 *)((u8 *)value + 0x30) = vector[0];
    *(f32 *)((u8 *)value + 0x34) = vector[1];
    *(f32 *)((u8 *)value + 0x38) = vector[2];
}
