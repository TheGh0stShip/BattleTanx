#include "types.h"

extern s32 gRuntimeSelection __asm__("D_80139610");

void set_runtime_selection(s32 selection) __asm__("func_800F3A14");

void set_runtime_selection(s32 selection)
{
    gRuntimeSelection = selection;
}
