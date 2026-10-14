#include "os_thread.h"

#define OS_STATE_STOPPED 1
#define OS_STATE_RUNNABLE 2
#define OS_STATE_WAITING 8

extern OSThread *D_801460F8;
extern OSThread *D_80146100;

extern u32 __osDisableInt(void);
extern void __osRestoreInt(u32);
extern void __osEnqueueThread(OSThread **, OSThread *);
extern OSThread *__osPopThread(OSThread **);
extern void __osDispatchThread(void);
extern void __osEnqueueAndYield(OSThread **);

void osStartThread(OSThread *thread)
{
    register u32 mask = __osDisableInt();

    switch (thread->state) {
    case OS_STATE_WAITING:
        thread->state = OS_STATE_RUNNABLE;
        __osEnqueueThread(&D_801460F8, thread);
        break;
    case OS_STATE_STOPPED:
        if (thread->queue == 0 || thread->queue == &D_801460F8) {
            thread->state = OS_STATE_RUNNABLE;
            __osEnqueueThread(&D_801460F8, thread);
        } else {
            thread->state = OS_STATE_WAITING;
            __osEnqueueThread(thread->queue, thread);
            __osEnqueueThread(&D_801460F8, __osPopThread(thread->queue));
        }
        break;
    }

    if (D_80146100 == 0) {
        __osDispatchThread();
    } else if (D_80146100->priority < D_801460F8->priority) {
        D_80146100->state = OS_STATE_RUNNABLE;
        __osEnqueueAndYield(&D_801460F8);
    }
    __osRestoreInt(mask);
}
