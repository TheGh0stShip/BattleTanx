/* Adapted from the BattleTanx: Global Assault libultra recovery. */
/* Data reconstruction: decompals/ultralib e24c836796df4bf520ff8b11a5c9d2cea3a66cbd src/io/aisetnextbuf.c: static u8 hdwrBugFlag = FALSE; (function-local) */
/* IDOFLAGS: -O1 -mips2 */
#include "ultra.h"

extern s32 __osAiDeviceBusy(void);
extern u32 osVirtualToPhysical(void *addr);

s32 osAiSetNextBuffer(void *bufPtr, u32 size)
{
    static u8 hdwrBugFlag = 0;
    char *bptr = bufPtr;

    if (hdwrBugFlag != 0)
        bptr -= 0x2000;

    if ((((u32)bufPtr + size) & 0x3FFF) == 0x2000)
        hdwrBugFlag = 1;
    else
        hdwrBugFlag = 0;

    if (__osAiDeviceBusy())
        return -1;

    IO_WRITE(AI_DRAM_ADDR_REG, osVirtualToPhysical(bptr));
    IO_WRITE(AI_LEN_REG, size);
    return 0;
}
