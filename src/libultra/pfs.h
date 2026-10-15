/* Adapted from the BattleTanx: Global Assault libultra recovery. */
#ifndef PFS_H
#define PFS_H

#include "controller.h"

#define BLOCKSIZE 32
#define PFS_LABEL_AREA 7
#define CONT_CMD_READ_MEMPACK 2
#define CONT_CMD_WRITE_MEMPACK 3
#define CONT_CMD_READ_MEMPACK_TX 3
#define CONT_CMD_READ_MEMPACK_RX 33
#define CONT_CMD_WRITE_MEMPACK_TX 35
#define CONT_CMD_WRITE_MEMPACK_RX 1
#define PFS_ERR_NOPACK 1
#define PFS_ERR_NEW_PACK 2
#define PFS_ERR_INCONSISTENT 3
#define PFS_ERR_CONTRFAIL 4
#define PFS_ERR_INVALID 5
#define PFS_ERR_BAD_DATA 6
#define PFS_DATA_FULL 7
#define PFS_DIR_FULL 8
#define PFS_ERR_EXIST 9
#define PFS_ERR_ID_FATAL 10
#define PFS_ERR_DEVICE 11

typedef struct {
    u8 dummy;
    u8 txsize;
    u8 rxsize;
    u8 cmd;
    u16 address;
    u8 data[BLOCKSIZE];
    u8 datacrc;
} __OSContRamReadFormat;

#define PFS_ID_0AREA 1
#define PFS_ID_1AREA 3
#define PFS_ID_2AREA 4
#define PFS_ID_3AREA 6
#define PFS_ONE_PAGE 8
#define PFS_MAX_BANKS 62
#define DEF_DIR_PAGES 2
#define PFS_INODE_SIZE_PER_PAGE 128
#define PFS_READ 0
#define PFS_WRITE 1
#define PFS_EOF 1
#define PFS_PAGE_NOT_EXIST 2
#define PFS_PAGE_NOT_USED 3
#define PFS_INITIALIZED 0x1
#define PFS_CORRUPTED 0x2
#define PFS_FILE_NAME_LEN 16
#define PFS_FILE_EXT_LEN 4

typedef struct {
    int status;
    OSMesgQueue *queue;
    int channel;
    u8 id[32];
    u8 label[32];
    int version;
    int dir_size;
    int inode_table;
    int minode_table;
    int dir_table;
    int inode_start_page;
    u8 banks;
    u8 activebank;
} OSPfs;

typedef struct {
    u32 repaired;
    u32 random;
    u64 serial_mid;
    u64 serial_low;
    u16 deviceid;
    u8 banks;
    u8 version;
    u16 checksum;
    u16 inverted_checksum;
} __OSPackId;

typedef union {
    struct {
        u8 bank;
        u8 page;
    } inode_t;
    u16 ipage;
} __OSInodeUnit;

typedef struct {
    __OSInodeUnit inode_page[128];
} __OSInode;

typedef struct {
    u32 game_code;
    u16 company_code;
    __OSInodeUnit start_page;
    u8 status;
    s8 reserved;
    u16 data_sum;
    u8 ext_name[PFS_FILE_EXT_LEN];
    u8 game_name[PFS_FILE_NAME_LEN];
} __OSDir;

#define ERRCK(fn) \
    ret = fn;     \
    if (ret != 0) \
        return ret;

#define SET_ACTIVEBANK_TO_ZERO              \
    if (pfs->activebank != 0) {             \
        pfs->activebank = 0;                \
        ERRCK(__osPfsSelectBank(pfs))       \
    }

#define PFS_CHECK_STATUS                            \
    if ((pfs->status & PFS_INITIALIZED) == 0)       \
        return PFS_ERR_INVALID;

#define PFS_CHECK_ID                                \
    if (__osCheckId(pfs) == PFS_ERR_NEW_PACK)       \
        return PFS_ERR_NEW_PACK;

extern OSPifRam __osPfsPifRam;
extern s32 __osContRamWrite(OSMesgQueue *mq, int channel, u16 address,
                            u8 *buffer, int force);
extern s32 __osContRamRead(OSMesgQueue *mq, int channel, u16 address,
                           u8 *buffer);
extern u8 __osContAddressCrc(u16 addr);
extern u8 __osContDataCrc(u8 *data);
extern s32 __osPfsGetStatus(OSMesgQueue *queue, int channel);
extern s32 __osPfsSelectBank(OSPfs *pfs);
extern s32 __osIdCheckSum(u16 *ptr, u16 *csum, u16 *icsum);
extern s32 __osRepairPackId(OSPfs *pfs, __OSPackId *badid,
                            __OSPackId *newid);
extern s32 __osCheckPackId(OSPfs *pfs, __OSPackId *temp);
extern s32 __osGetId(OSPfs *pfs);
extern s32 __osCheckId(OSPfs *pfs);
extern s32 __osPfsRWInode(OSPfs *pfs, __OSInode *inode, u8 flag, u8 bank);
extern s32 osPfsFindFile(OSPfs *pfs, u16 company_code, u32 game_code,
                         u8 *game_name, u8 *ext_name, s32 *file_no);
extern s32 __osPfsReleasePages(OSPfs *pfs, __OSInode *inode, u8 start_page,
                               u16 *sum, u8 bank,
                               __OSInodeUnit *final_page, int flag);
extern s32 __osBlockSum(OSPfs *pfs, u8 page_no, u16 *sum, u8 bank);
extern u16 __osSumcalc(u8 *ptr, int length);

#endif
