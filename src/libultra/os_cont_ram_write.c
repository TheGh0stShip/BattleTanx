/* Adapted from the BattleTanx: Global Assault libultra recovery. */
/* IDO 5.3: -O1 -mips2; LDSYM __osPfsPifRam=0x803C6290 */
#include "pfs.h"

static void __osPackRamWriteData(int channel, u16 address, u8 *buffer);

s32 __osContRamWrite(OSMesgQueue *mq, int channel, u16 address, u8 *buffer,
                     int force)
{
    s32 ret = 0;
    int i;
    u8 *ptr;
    __OSContRamReadFormat ramreadformat;
    int retry;

    ptr = (u8 *)&__osPfsPifRam;
    retry = 2;
    if ((force != 1) && (address < PFS_LABEL_AREA) && (address != 0))
        return 0;
    __osSiGetAccess();
    __osContLastCmd = CONT_CMD_WRITE_MEMPACK;
    __osPackRamWriteData(channel, address, buffer);
    ret = __osSiRawStartDma(OS_WRITE, &__osPfsPifRam);
    osRecvMesg(mq, 0, OS_MESG_BLOCK);
    do {
        ret = __osSiRawStartDma(OS_READ, &__osPfsPifRam);
        osRecvMesg(mq, 0, OS_MESG_BLOCK);
        ptr = (u8 *)&__osPfsPifRam;
        if (channel != 0)
            for (i = 0; i < channel; i++)
                ptr++;
        ramreadformat = *(__OSContRamReadFormat *)ptr;
        ret = CHNL_ERR(ramreadformat);
        if (ret == 0) {
            if (__osContDataCrc(buffer) != ramreadformat.datacrc) {
                ret = __osPfsGetStatus(mq, channel);
                if (ret != 0) {
                    __osSiRelAccess();
                    return ret;
                }
                ret = PFS_ERR_CONTRFAIL;
            }
        } else {
            ret = PFS_ERR_NOPACK;
        }
    } while ((ret == PFS_ERR_CONTRFAIL) && (retry-- >= 0));
    __osSiRelAccess();
    return ret;
}

static void __osPackRamWriteData(int channel, u16 address, u8 *buffer)
{
    u8 *ptr;
    __OSContRamReadFormat ramreadformat;
    int i;

    ptr = (u8 *)&__osPfsPifRam;
    for (i = 0; i < PIFRAM_WORDS; i++)
        ((u32 *)&__osPfsPifRam)[i] = 0;
    __osPfsPifRam.pifstatus = CONT_CMD_EXE;
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
