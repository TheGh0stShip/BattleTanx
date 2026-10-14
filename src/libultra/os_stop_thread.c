#include "os_thread.h"

#define OS_STATE_STOPPED 1
#define OS_STATE_RUNNABLE 2
#define OS_STATE_RUNNING 4
#define OS_STATE_WAITING 8

extern OSThread *D_80146100;

extern u32 __osDisableInt(void);
extern void __osRestoreInt(u32);
extern void __osDequeueThread(OSThread **, OSThread *);
extern void __osEnqueueAndYield(OSThread **);

void osStopThread(OSThread *thread)
{
    register u32 mask;
    register u16 state;

    mask = __osDisableInt();
    state = thread == 0 ? OS_STATE_RUNNING : thread->state;
    switch (state) {
    case OS_STATE_RUNNING:
        D_80146100->state = OS_STATE_STOPPED;
        __osEnqueueAndYield(0);
        break;
    case OS_STATE_RUNNABLE:
    case OS_STATE_WAITING:
        thread->state = OS_STATE_STOPPED;
        __osDequeueThread(thread->queue, thread);
        break;
    }
    __osRestoreInt(mask);
}
