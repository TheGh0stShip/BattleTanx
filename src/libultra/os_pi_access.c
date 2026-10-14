/* libultra 2.0I io/piacs.c: PI manager access queue. */
#include "ultra.h"

#define PI_Q_BUF_LEN 1

extern u32 D_80145DF0; /* __osPiAccessQueueEnabled */
extern OSMesg D_803C7520[PI_Q_BUF_LEN]; /* piAccessBuf */
extern OSMesgQueue D_803C7528; /* __osPiAccessQueue */

void __osPiCreateAccessQueue(void)
{
    D_80145DF0 = 1;
    osCreateMesgQueue(&D_803C7528, D_803C7520, PI_Q_BUF_LEN);
    osSendMesg(&D_803C7528, 0, OS_MESG_NOBLOCK);
}

void __osPiGetAccess(void)
{
    OSMesg dummyMesg;

    if (!D_80145DF0) {
        __osPiCreateAccessQueue();
    }
    osRecvMesg(&D_803C7528, &dummyMesg, OS_MESG_BLOCK);
}

void __osPiRelAccess(void)
{
    osSendMesg(&D_803C7528, 0, OS_MESG_NOBLOCK);
}
