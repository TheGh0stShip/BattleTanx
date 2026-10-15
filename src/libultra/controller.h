/* Adapted from the BattleTanx: Global Assault libultra recovery. */
/* Shared libultra controller state (owned by the controller.c unit's .bss). */
#ifndef CONTROLLER_H
#define CONTROLLER_H
#include "ultra.h"

#define MAXCONTROLLERS 4
#define CONT_CMD_REQUEST_STATUS 0
#define CONT_CMD_READ_BUTTON 1
#define CONT_CMD_REQUEST_STATUS_TX 1
#define CONT_CMD_REQUEST_STATUS_RX 3
#define CONT_CMD_READ_BUTTON_TX 1
#define CONT_CMD_READ_BUTTON_RX 4
#define CONT_CMD_EXE 1
#define CONT_CMD_END 0xFE
#define CONT_CMD_NOP 0xFF
#define CHNL_ERR(format) (((format).rxsize & 0xC0) >> 4)

typedef struct {
    u32 ramarray[15];
    u32 pifstatus;
} OSPifRam;                     /* 0x40 */
#define PIFRAM_WORDS 16         /* ramarray plus pifstatus, cleared as one block */

typedef struct {
    u8 dummy;
    u8 txsize;
    u8 rxsize;
    u8 cmd;
    u8 typeh;
    u8 typel;
    u8 status;
    u8 dummy1;
} __OSContRequesFormat;

typedef struct {
    u8 dummy;
    u8 txsize;
    u8 rxsize;
    u8 cmd;
    u16 button;
    s8 stick_x;
    s8 stick_y;
} __OSContReadFormat;

typedef struct {
    u16 type;
    u8 status;
    u8 errno;
} OSContStatus;

typedef struct {
    u16 button;
    s8 stick_x;
    s8 stick_y;
    u8 errno;
} OSContPad;

extern OSPifRam __osContPifRam;
extern u8 __osContLastCmd;
extern u8 __osMaxControllers;

extern void __osSiGetAccess(void);
extern void __osSiRelAccess(void);
extern s32 __osSiRawStartDma(s32 direction, void *dramAddr);
extern void __osPackRequestData(u8 cmd);
extern void __osContGetInitData(u8 *pattern, OSContStatus *data);
#endif
