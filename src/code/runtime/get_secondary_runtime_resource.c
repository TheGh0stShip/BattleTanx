#include "types.h"

extern s32 gSecondaryRuntimeResource __asm__("D_801C9170");

s32 get_secondary_runtime_resource(void) __asm__("func_800821C0");

s32 get_secondary_runtime_resource(void)
{
    return gSecondaryRuntimeResource;
}
