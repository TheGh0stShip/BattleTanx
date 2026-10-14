/* libultra 2.0I os/resetglobalintmask.c */
#include "ultra.h"

extern u32 D_80145DB0; /* __OSGlobalIntMask */

void __osResetGlobalIntMask(OSIntMask mask)
{
    register u32 saveMask = __osDisableInt();

    D_80145DB0 &= ~(mask & ~0x401);
    __osRestoreInt(saveMask);
}
