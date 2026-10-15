/* Adapted from the BattleTanx: Global Assault libultra recovery. */
/* IDOFLAGS: -O1 -mips2
   LDSYM __osContPifRam=0x803C4D80 LDSYM __osContLastCmd=0x803C4DC0 LDSYM __osMaxControllers=0x803C4DC1 */
#include "controller.h"

static void __osPackReadData(void);

s32 osContStartReadData(OSMesgQueue *mq)
{
    s32 ret = 0;
    int i;

    __osSiGetAccess();
    if (__osContLastCmd != CONT_CMD_READ_BUTTON) {
        __osPackReadData();
        ret = __osSiRawStartDma(OS_WRITE, &__osContPifRam);
        osRecvMesg(mq, 0, OS_MESG_BLOCK);
    }
    for (i = 0; i < PIFRAM_WORDS; i++)
        ((u32 *)&__osContPifRam)[i] = CONT_CMD_NOP;
    __osContPifRam.pifstatus = 0;
    ret = __osSiRawStartDma(OS_READ, &__osContPifRam);
    __osContLastCmd = CONT_CMD_READ_BUTTON;
    __osSiRelAccess();
    return ret;
}

void osContGetReadData(OSContPad *data)
{
    u8 *ptr;
    __OSContReadFormat readformat;
    int i;

    ptr = (u8 *)&__osContPifRam;
    for (i = 0; i < __osMaxControllers; i++, ptr += sizeof(readformat), data++) {
        readformat = *(__OSContReadFormat *)ptr;
        data->errno = CHNL_ERR(readformat);
        if (data->errno == 0) {
            data->button = readformat.button;
            data->stick_x = readformat.stick_x;
            data->stick_y = readformat.stick_y;
        }
    }
}

static void __osPackReadData(void)
{
    u8 *ptr;
    __OSContReadFormat readformat;
    int i;

    ptr = (u8 *)&__osContPifRam;
    for (i = 0; i < PIFRAM_WORDS; i++)
        ((u32 *)&__osContPifRam)[i] = 0;
    __osContPifRam.pifstatus = CONT_CMD_EXE;
    readformat.dummy = CONT_CMD_NOP;
    readformat.txsize = CONT_CMD_READ_BUTTON_TX;
    readformat.rxsize = CONT_CMD_READ_BUTTON_RX;
    readformat.cmd = CONT_CMD_READ_BUTTON;
    readformat.button = 0xFFFF;
    readformat.stick_x = -1;
    readformat.stick_y = -1;
    for (i = 0; i < __osMaxControllers; i++) {
        *(__OSContReadFormat *)ptr = readformat;
        ptr += sizeof(readformat);
    }
    *ptr = CONT_CMD_END;
}
