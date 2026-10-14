#include "os_thread.h"

#define OS_STATE_STOPPED 1
#define OS_STATE_RUNNABLE 2

extern OSThread *D_801460F8;
extern OSThread *D_80146100;

extern u32 __osDisableInt(void);
extern void __osRestoreInt(u32);
extern void __osDequeueThread(OSThread **, OSThread *);
extern void __osEnqueueThread(OSThread **, OSThread *);
extern void __osEnqueueAndYield(OSThread **);

void osSetThreadPri(OSThread *thread, OSPri priority)
{
    register u32 mask;

    mask = __osDisableInt();
    if (thread == 0) {
        thread = D_80146100;
    }
    if (thread->priority != priority) {
        thread->priority = priority;
        if (thread != D_80146100 && thread->state != OS_STATE_STOPPED) {
            __osDequeueThread(thread->queue, thread);
            __osEnqueueThread(thread->queue, thread);
        }
        if (D_80146100->priority < D_801460F8->priority) {
            D_80146100->state = OS_STATE_RUNNABLE;
            __osEnqueueAndYield(&D_801460F8);
        }
    }
    __osRestoreInt(mask);
}
