#include "os_thread.h"

#define OS_STATE_STOPPED 1

extern OSThread *D_801460FC;
extern OSThread *D_80146100;

extern u32 __osDisableInt(void);
extern void __osRestoreInt(u32);
extern void __osDequeueThread(OSThread **, OSThread *);
extern void __osDispatchThread(void);

void osDestroyThread(OSThread *thread)
{
    register u32 mask;
    register OSThread *previous;
    register OSThread *next;

    mask = __osDisableInt();
    if (thread == 0) {
        thread = D_80146100;
    } else if (thread->state != OS_STATE_STOPPED) {
        __osDequeueThread(thread->queue, thread);
    }

    if (D_801460FC == thread) {
        D_801460FC = D_801460FC->tlnext;
    } else {
        previous = D_801460FC;
        while ((next = previous->tlnext) != 0) {
            if (next == thread) {
                previous->tlnext = thread->tlnext;
                break;
            }
            previous = next;
        }
    }

    if (thread == D_80146100) {
        __osDispatchThread();
    }
    __osRestoreInt(mask);
}
