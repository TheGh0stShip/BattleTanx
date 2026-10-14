#include "types.h"

extern u8 gRuntimeInitialized __asm__("D_80125780");

void mark_runtime_initialized(void) __asm__("func_8007C6C4");

void mark_runtime_initialized(void)
{
    gRuntimeInitialized = 1;
}
