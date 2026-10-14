#include "types.h"

extern s32 D_80137904;

void set_runtime_slot_index(s32 index) __asm__("func_800EC380");

void set_runtime_slot_index(s32 index)
{
    D_80137904 = index;
}
