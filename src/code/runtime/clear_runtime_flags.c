#include "types.h"

extern u8 gRuntimeFlag0 __asm__("D_8033B630");
extern u8 gRuntimeFlag1 __asm__("D_8033B631");

void clear_runtime_flags(void) __asm__("func_800EE4BC");

void clear_runtime_flags(void)
{
    gRuntimeFlag1 = 0;
    gRuntimeFlag0 = 0;
}
