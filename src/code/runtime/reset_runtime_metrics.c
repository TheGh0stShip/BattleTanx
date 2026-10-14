#include "types.h"

extern s32 gRuntimeMetric0 __asm__("D_80125D40");
extern s32 gRuntimeMetric1 __asm__("D_80125D44");
extern u16 gRuntimeMetric2 __asm__("D_80125D48");

void reset_runtime_metrics(void) __asm__("func_80093D30");

void reset_runtime_metrics(void)
{
    gRuntimeMetric0 = 0;
    gRuntimeMetric1 = 0;
    gRuntimeMetric2 = 0;
}
