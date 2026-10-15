/* Adapted from the BattleTanx: Global Assault libultra recovery. */
#include "pfs.h"

extern s32 osPfsChecker(OSPfs *pfs);

s32 osPfsInitPak(OSMesgQueue *queue, OSPfs *pfs, int channel)
{
    int k;
    s32 ret = 0;
    u16 sum;
    u16 isum;
    u8 temp[BLOCKSIZE];
    __OSPackId *id;
    __OSPackId newid;

    __osSiGetAccess();
    ret = __osPfsGetStatus(queue, channel);
    __osSiRelAccess();
    if (ret != 0)
        return ret;
    pfs->queue = queue;
    pfs->channel = channel;
    pfs->status = 0;
    pfs->activebank = 0;
    ERRCK(__osPfsSelectBank(pfs));
    __osIdCheckSum((u16 *)temp, &sum, &isum);
    id = (__OSPackId *)temp;
    if ((id->checksum != sum) || (id->inverted_checksum != isum)) {
        ERRCK(__osCheckPackId(pfs, id));
        if (ret != 0)
            return ret;
    }
    if ((id->deviceid & 1) == 0) {
        ERRCK(__osRepairPackId(pfs, id, &newid));
        id = &newid;
        if ((id->deviceid & 1) == 0)
            return PFS_ERR_DEVICE;
    }
    for (k = 0; k < BLOCKSIZE; k++)
        pfs->id[k] = ((u8 *)id)[k];
    pfs->version = id->version;
    pfs->banks = id->banks;
    pfs->inode_start_page = 1 + DEF_DIR_PAGES + (2 * pfs->banks);
    pfs->dir_size = DEF_DIR_PAGES * PFS_ONE_PAGE;
    pfs->inode_table = 1 * PFS_ONE_PAGE;
    pfs->minode_table = (1 + pfs->banks) * PFS_ONE_PAGE;
    pfs->dir_table = pfs->minode_table + (pfs->banks * PFS_ONE_PAGE);
    ERRCK(__osContRamRead(pfs->queue, pfs->channel, PFS_LABEL_AREA,
                          pfs->label));
    ret = osPfsChecker(pfs);
    pfs->status |= PFS_INITIALIZED;
    return ret;
}
