#include "types.h"

void update_runtime_workspace_byte(u8 *workspace, u16 index, s32 arg2, u16 increment)
    __asm__("func_800DEC28");

void update_runtime_workspace_byte(u8 *workspace, u16 index, s32 arg2, u16 increment)
{
    if (increment == 0) {
        workspace[index] = 0;
    } else {
        workspace[index]++;
    }
}
