/* Adapted from the BattleTanx: Global Assault libultra recovery. */
/* LDSYM __osPfsPifRam=0x803C6290 */
#include "pfs.h"

#define CONT_CARD_ON 0x01
#define CONT_ADDR_CRC_ER 0x04

void __osPfsRequestData(u8 cmd);
void __osPfsGetInitData(u8 *pattern, OSContStatus *data);

s32 osPfsIsPlug(OSMesgQueue *queue, u8 *pattern)
{
    s32 ret = 0;
    OSMesg dummy;
    u8 bitpattern;
    OSContStatus data[MAXCONTROLLERS];
    int channel;
    u8 bits = 0;
    int crc_error_cnt = 3;

    __osSiGetAccess();
    while (1) {
        __osPfsRequestData(CONT_CMD_REQUEST_STATUS);
        ret = __osSiRawStartDma(OS_WRITE, &__osPfsPifRam);
        osRecvMesg(queue, &dummy, OS_MESG_BLOCK);
        ret = __osSiRawStartDma(OS_READ, &__osPfsPifRam);
        osRecvMesg(queue, &dummy, OS_MESG_BLOCK);
        __osPfsGetInitData(&bitpattern, data);
        for (channel = 0; channel < __osMaxControllers; channel++) {
            if ((data[channel].status & CONT_ADDR_CRC_ER) == 0) {
                crc_error_cnt--;
                break;
            }
        }
        if (__osMaxControllers == channel)
            crc_error_cnt = 0;
        if (crc_error_cnt < 1)
            break;
    }
    for (channel = 0; channel < __osMaxControllers; channel++) {
        if ((data[channel].errno == 0) &&
            ((data[channel].status & CONT_CARD_ON) != 0))
            bits |= (1 << channel);
    }
    __osSiRelAccess();
    *pattern = bits;
    return ret;
}

void __osPfsRequestData(u8 cmd)
{
    u8 *ptr;
    __OSContRequesFormat requestformat;
    int i;

    __osContLastCmd = cmd;
    for (i = 0; i < PIFRAM_WORDS; i++)
        ((u32 *)&__osPfsPifRam)[i] = 0;
    __osPfsPifRam.pifstatus = CONT_CMD_EXE;
    ptr = (u8 *)&__osPfsPifRam;
    requestformat.dummy = CONT_CMD_NOP;
    requestformat.txsize = CONT_CMD_REQUEST_STATUS_TX;
    requestformat.rxsize = CONT_CMD_REQUEST_STATUS_RX;
    requestformat.cmd = cmd;
    requestformat.typeh = CONT_CMD_NOP;
    requestformat.typel = CONT_CMD_NOP;
    requestformat.status = CONT_CMD_NOP;
    requestformat.dummy1 = CONT_CMD_NOP;
    for (i = 0; i < __osMaxControllers; i++) {
        *(__OSContRequesFormat *)ptr = requestformat;
        ptr += sizeof(requestformat);
    }
    *ptr = CONT_CMD_END;
}

void __osPfsGetInitData(u8 *pattern, OSContStatus *data)
{
    u8 *ptr;
    __OSContRequesFormat requestformat;
    int i;
    u8 bits = 0;

    ptr = (u8 *)&__osPfsPifRam;
    for (i = 0; i < __osMaxControllers;
         i++, ptr += sizeof(requestformat), data++) {
        requestformat = *(__OSContRequesFormat *)ptr;
        data->errno = CHNL_ERR(requestformat);
        if (data->errno == 0) {
            data->type = (requestformat.typel << 8) | requestformat.typeh;
            data->status = requestformat.status;
            bits |= 1 << i;
        }
    }
    *pattern = bits;
}
