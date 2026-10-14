/* Minimal libultra declarations for the 0x801029F0-0x801037B0 units (o32, big-endian). */
#ifndef ULTRA_H
#define ULTRA_H
#include "types.h"

#define IO_READ(addr) (*(volatile u32 *)(addr))
#define IO_WRITE(addr, data) (*(volatile u32 *)(addr) = (u32)(data))
#define PHYS_TO_K1(x) ((u32)(x) | 0xA0000000)

#define AI_DRAM_ADDR_REG 0xA4500000
#define AI_LEN_REG 0xA4500004
#define AI_CONTROL_REG 0xA4500008
#define AI_STATUS_REG 0xA450000C
#define AI_DACRATE_REG 0xA4500010
#define AI_BITRATE_REG 0xA4500014
#define AI_CONTROL_DMA_ON 1
#define AI_MIN_DACRATE 132
#define AI_MAX_BITRATE 16

typedef void *OSMesg;
typedef u32 OSIntMask;
typedef s32 OSPri;
typedef s32 OSId;

typedef struct {
    u32 errStatus;
    void *dramAddr;
    void *C2Addr;
    u32 sectorSize;
    u32 C1ErrNum;
    u32 C1ErrSector[4];
} __OSBlockInfo;

typedef struct {
    u32 cmdType;
    u16 transferMode;
    u16 blockNum;
    s32 sectorNum;
    u32 devAddr;
    u32 bmCtlShadow;
    u32 seqCtlShadow;
    __OSBlockInfo block[2];
} __OSTranxInfo;                /* 0x60 */

typedef struct OSPiHandle_s {
    struct OSPiHandle_s *next; /* 0x00 */
    u8 type;                   /* 0x04 */
    u8 latency;                /* 0x05 */
    u8 pageSize;               /* 0x06 */
    u8 relDuration;            /* 0x07 */
    u8 pulse;                  /* 0x08 */
    u8 domain;                 /* 0x09 */
    u32 baseAddress;           /* 0x0C */
    u32 speed;                 /* 0x10 */
    __OSTranxInfo transferInfo; /* 0x14 */
} OSPiHandle;

typedef struct OSMesgQueue_s {
    void *mtqueue;
    void *fullqueue;
    s32 validCount;
    s32 first;
    s32 msgCount;
    OSMesg *msg;
} OSMesgQueue;                  /* 0x18 */

typedef u64 OSTime;

typedef struct OSTimer_s {
    struct OSTimer_s *next;
    struct OSTimer_s *prev;
    OSTime interval;
    OSTime value;
    OSMesgQueue *mq;
    OSMesg msg;
} OSTimer;                      /* 0x20 */

#define OS_MESG_NOBLOCK 0
#define OS_MESG_BLOCK 1
#define OS_READ 0
#define OS_WRITE 1

typedef struct {
    u16 type;
    u8 pri;
    u8 status;
    OSMesgQueue *retQueue;
} OSIoMesgHdr;

typedef struct {
    OSIoMesgHdr hdr;
    void *dramAddr;
    u32 devAddr;
    u32 size;
    OSPiHandle *piHandle;
} OSIoMesg;

#define OS_MESG_PRI_NORMAL 0
#define OS_MESG_PRI_HIGH 1
#define OS_MESG_TYPE_EDMAREAD 15
#define OS_MESG_TYPE_EDMAWRITE 16

extern s32 osSendMesg(OSMesgQueue *mq, OSMesg msg, s32 flag);
extern s32 osJamMesg(OSMesgQueue *mq, OSMesg msg, s32 flag);
extern OSMesgQueue *osPiGetCmdQueue(void);
extern s32 osRecvMesg(OSMesgQueue *mq, OSMesg *msg, s32 flag);
extern void osCreateMesgQueue(OSMesgQueue *mq, OSMesg *msg, s32 count);
extern OSIntMask __osDisableInt(void);
extern void __osRestoreInt(OSIntMask im);
extern void _bzero(void *p, s32 len);
extern void _bcopy(const void *src, void *dst, s32 len);
#endif
