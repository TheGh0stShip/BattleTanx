#include "types.h"

extern s32 gRuntimeResource __asm__("D_80125850");
s32 get_runtime_resource(void) __asm__("func_80081AC0");

s32 get_runtime_resource(void)
{
    return gRuntimeResource;
}
