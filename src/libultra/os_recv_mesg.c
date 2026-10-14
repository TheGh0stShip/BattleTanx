#include "os_thread.h"

#define OS_STATE_WAITING 8

extern OSThread *D_80146100;

extern void __osEnqueueAndYield(OSThread **);
extern OSThread *__osPopThread(OSThread **);
extern void osStartThread(OSThread *);

s32 osRecvMesg(OSMesgQueue *queue, OSMesg *message, s32 flag)
{
    register u32 mask;

    mask = __osDisableInt();
    while (queue->validCount == 0) {
        if (flag == OS_MESG_NOBLOCK) {
            __osRestoreInt(mask);
            return -1;
        }
        D_80146100->state = OS_STATE_WAITING;
        __osEnqueueAndYield((OSThread **)&queue->mtqueue);
    }
    if (message != 0) {
        *message = queue->msg[queue->first];
    }
    queue->first = (queue->first + 1) % queue->msgCount;
    queue->validCount--;
    if (((OSThread *)queue->fullqueue)->next != 0) {
        osStartThread(__osPopThread((OSThread **)&queue->fullqueue));
    }
    __osRestoreInt(mask);
    return 0;
}
