#include "types.h"

extern s8 gRuntimeWorkspaceEnd __asm__("D_8032900F");

void clear_runtime_workspace(void) __asm__("func_800DEC04");

void clear_runtime_workspace(void)
{
    s32 remaining = 0xBB7;
    s8 *cursor = &gRuntimeWorkspaceEnd;

    do {
        *cursor = 0;
        remaining--;
        cursor--;
    } while (remaining >= 0);
}
