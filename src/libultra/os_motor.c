/* Adapted from the BattleTanx: Global Assault libultra recovery. */
/* IDOFLAGS: -O1 -mips2
   BSS_VRAM 0x803C6050: _MotorStopData[4], _MotorStartData[4], _motorstopbuf[32], _motorstartbuf[32] (0x240 bytes).
   LDSYM __osPfsPifRam=0x803C6290 LDSYM __osContLastCmd=0x803C4DC0 */
#include "pfs.h"


static OSPifRam _MotorStopData[MAXCONTROLLERS];
static OSPifRam _MotorStartData[MAXCONTROLLERS];
static u8 _motorstopbuf[32];
static u8 _motorstartbuf[32];

static void _MakeMotorData(int channel, u16 address, u8 *buffer, OSPifRam *mdata);

s32 osMotorStop(OSPfs *pfs)
{
    int i;
    s32 ret;
    u8 *ptr;
    __OSContRamReadFormat ramreadformat;

    ptr = (u8 *)&__osPfsPifRam;
    __osSiGetAccess();
    __osContLastCmd = CONT_CMD_WRITE_MEMPACK;
    __osSiRawStartDma(OS_WRITE, &_MotorStopData[pfs->channel]);
    osRecvMesg(pfs->queue, 0, OS_MESG_BLOCK);
    ret = __osSiRawStartDma(OS_READ, &__osPfsPifRam);
    osRecvMesg(pfs->queue, 0, OS_MESG_BLOCK);
    ptr = (u8 *)&__osPfsPifRam;
    if (pfs->channel != 0)
        for (i = 0; i < pfs->channel; i++)
            ptr++;
    ramreadformat = *(__OSContRamReadFormat *)ptr;
    ret = CHNL_ERR(ramreadformat);
    if (ret == 0 && ramreadformat.datacrc != 0)
        ret = PFS_ERR_CONTRFAIL;
    __osSiRelAccess();
    return ret;
}

s32 osMotorStart(OSPfs *pfs)
{
    int i;
    s32 ret;
    u8 *ptr;
    __OSContRamReadFormat ramreadformat;

    ptr = (u8 *)&__osPfsPifRam;
    __osSiGetAccess();
    __osContLastCmd = CONT_CMD_WRITE_MEMPACK;
    __osSiRawStartDma(OS_WRITE, &_MotorStartData[pfs->channel]);
    osRecvMesg(pfs->queue, 0, OS_MESG_BLOCK);
    ret = __osSiRawStartDma(OS_READ, &__osPfsPifRam);
    osRecvMesg(pfs->queue, 0, OS_MESG_BLOCK);
    ptr = (u8 *)&__osPfsPifRam;
    if (pfs->channel != 0)
        for (i = 0; i < pfs->channel; i++)
            ptr++;
    ramreadformat = *(__OSContRamReadFormat *)ptr;
    ret = CHNL_ERR(ramreadformat);
    if (ret == 0 && ramreadformat.datacrc != 0xEB)
        ret = PFS_ERR_CONTRFAIL;
    __osSiRelAccess();
    return ret;
}

static void _MakeMotorData(int channel, u16 address, u8 *buffer, OSPifRam *mdata)
{
    u8 *ptr;
    __OSContRamReadFormat ramreadformat;
    int i;

    ptr = (u8 *)mdata->ramarray;
    for (i = 0; i < 15; i++)
        mdata->ramarray[i] = 0;
    mdata->pifstatus = CONT_CMD_EXE;
    ramreadformat.dummy = CONT_CMD_NOP;
    ramreadformat.txsize = CONT_CMD_WRITE_MEMPACK_TX;
    ramreadformat.rxsize = CONT_CMD_WRITE_MEMPACK_RX;
    ramreadformat.cmd = CONT_CMD_WRITE_MEMPACK;
    ramreadformat.address = (address << 5) | __osContAddressCrc(address);
    ramreadformat.datacrc = CONT_CMD_NOP;
    for (i = 0; i < BLOCKSIZE; i++)
        ramreadformat.data[i] = *buffer++;
    if (channel != 0)
        for (i = 0; i < channel; i++)
            *ptr++ = 0;
    *(__OSContRamReadFormat *)ptr = ramreadformat;
    ptr += sizeof(__OSContRamReadFormat);
    ptr[0] = CONT_CMD_END;
}

s32 osMotorInit(OSMesgQueue *mq, OSPfs *pfs, int channel)
{
    int i;
    s32 ret;
    u8 temp[32];

    pfs->queue = mq;
    pfs->channel = channel;
    pfs->status = 0;
    pfs->activebank = 0x80;
    for (i = 0; i < 32; i++)
        temp[i] = 0x80;
    ret = __osContRamWrite(mq, channel, 0x400, temp, 0);
    if (ret == PFS_ERR_NEW_PACK)
        ret = __osContRamWrite(mq, channel, 0x400, temp, 0);
    if (ret != 0)
        return ret;
    ret = __osContRamRead(mq, channel, 0x400, temp);
    if (ret == PFS_ERR_NEW_PACK)
        ret = PFS_ERR_CONTRFAIL;
    if (ret != 0)
        return ret;
    if (temp[31] != 0x80)
        return PFS_ERR_DEVICE;
    for (i = 0; i < 32; i++) {
        _motorstartbuf[i] = 1;
        _motorstopbuf[i] = 0;
    }
    _MakeMotorData(channel, 0x600, _motorstartbuf, &_MotorStartData[channel]);
    _MakeMotorData(channel, 0x600, _motorstopbuf, &_MotorStopData[channel]);
    return 0;
}
