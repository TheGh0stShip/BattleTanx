/* libultra 2.0I io/contquery.c */
#include "ultra.h"

#define CONT_CMD_REQUEST_STATUS 0

typedef struct {
    u16 type;
    u8 status;
    u8 errno;
} OSContStatus;

extern u8 D_803C4D80[]; /* __osContPifRam */
extern u8 D_803C4DC0;   /* __osContLastCmd */

extern void __osSiGetAccess(void);
extern void __osSiRelAccess(void);
extern void __osPackRequestData(u8 command);
extern s32 __osSiRawStartDma(s32 direction, void *dramAddr);
extern void __osContGetInitData(u8 *pattern, OSContStatus *data);

s32 osContStartQuery(OSMesgQueue *mq)
{
    s32 ret = 0;

    __osSiGetAccess();
    if (D_803C4DC0 != CONT_CMD_REQUEST_STATUS) {
        __osPackRequestData(CONT_CMD_REQUEST_STATUS);
        ret = __osSiRawStartDma(OS_WRITE, D_803C4D80);
        osRecvMesg(mq, 0, OS_MESG_BLOCK);
    }
    ret = __osSiRawStartDma(OS_READ, D_803C4D80);
    D_803C4DC0 = CONT_CMD_REQUEST_STATUS;
    __osSiRelAccess();
    return ret;
}

void osContGetQuery(OSContStatus *data)
{
    u8 pattern;

    __osContGetInitData(&pattern, data);
}
