#include "types.h"

extern s32 D_80137908;

s32 get_runtime_status(void) __asm__("func_800ECB98");

s32 get_runtime_status(void)
{
    return D_80137908;
}
