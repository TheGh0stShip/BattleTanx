#include "os_thread.h"

#define OS_STATE_WAITING 8

extern OSThread *D_80146100;

extern void __osEnqueueAndYield(OSThread **);
extern OSThread *__osPopThread(OSThread **);
extern void osStartThread(OSThread *);

s32 osJamMesg(OSMesgQueue *queue, OSMesg message, s32 flag)
{
    register u32 mask;

    mask = __osDisableInt();
    while (queue->validCount >= queue->msgCount) {
        if (flag == OS_MESG_BLOCK) {
            D_80146100->state = OS_STATE_WAITING;
            __osEnqueueAndYield((OSThread **)&queue->fullqueue);
        } else {
            __osRestoreInt(mask);
            return -1;
        }
    }
    queue->first = (queue->first + queue->msgCount - 1) % queue->msgCount;
    queue->msg[queue->first] = message;
    queue->validCount++;
    if (((OSThread *)queue->mtqueue)->next != 0) {
        osStartThread(__osPopThread((OSThread **)&queue->mtqueue));
    }
    __osRestoreInt(mask);
    return 0;
}
