#include "types.h"

#define MAXCONTROLLERS 4
#define OS_WRITE 1
#define OS_READ 0
#define OS_MESG_BLOCK 1

typedef void *OSMesg;
typedef struct OSMesgQueue OSMesgQueue;
typedef struct OSContStatus {
    u16 type;
    u8 status;
    u8 errno;
} OSContStatus;

extern u8 D_803C6290;
extern void __osPfsRequestData(u8 command);
extern s32 __osSiRawStartDma(s32 direction, void *address);
extern s32 osRecvMesg(OSMesgQueue *queue, OSMesg *message, s32 flags);
extern void __osPfsGetInitData(u8 *pattern, OSContStatus *data);

s32 __osPfsGetStatus(OSMesgQueue *queue, s32 channel)
{
    s32 result = 0;
    OSMesg message;
    u8 pattern;
    OSContStatus data[MAXCONTROLLERS];

    __osPfsRequestData(0);
    result = __osSiRawStartDma(OS_WRITE, &D_803C6290);
    osRecvMesg(queue, &message, OS_MESG_BLOCK);
    result = __osSiRawStartDma(OS_READ, &D_803C6290);
    osRecvMesg(queue, &message, OS_MESG_BLOCK);
    __osPfsGetInitData(&pattern, data);
    if ((data[channel].status & 1) != 0 && (data[channel].status & 2) != 0) {
        return 2;
    }
    if (data[channel].errno != 0 || (data[channel].status & 1) == 0) {
        return 1;
    }
    if ((data[channel].status & 4) != 0) {
        return 4;
    }
    return result;
}
