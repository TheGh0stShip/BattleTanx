#include "os_thread.h"

#define OS_STATE_RUNNABLE 2

extern OSThread *D_801460F8;
extern OSThread *D_80146100;

extern u32 __osDisableInt(void);
extern void __osRestoreInt(u32);
extern void __osEnqueueAndYield(OSThread **);

void osYieldThread(void)
{
    register u32 mask;

    mask = __osDisableInt();
    D_80146100->state = OS_STATE_RUNNABLE;
    __osEnqueueAndYield(&D_801460F8);
    __osRestoreInt(mask);
}
