#include "ultra.h"

#define SI_DRAM_ADDR_REG 0xA4800000
#define SI_PIF_ADDR_RD64B_REG 0xA4800004
#define SI_PIF_ADDR_WR64B_REG 0xA4800010
#define PIF_RAM_START 0x1FC007C0
#define PIF_RAM_SIZE 0x40

extern s32 __osSiDeviceBusy(void);
extern u32 osVirtualToPhysical(void *);
extern void osWritebackDCache(void *, s32);
extern void osInvalDCache(void *, s32);

s32 __osSiRawStartDma(s32 direction, void *dram_address)
{
    if (__osSiDeviceBusy()) {
        return -1;
    }
    if (direction == OS_WRITE) {
        osWritebackDCache(dram_address, PIF_RAM_SIZE);
    }
    IO_WRITE(SI_DRAM_ADDR_REG, osVirtualToPhysical(dram_address));
    if (direction == OS_READ) {
        IO_WRITE(SI_PIF_ADDR_RD64B_REG, PIF_RAM_START);
    } else {
        IO_WRITE(SI_PIF_ADDR_WR64B_REG, PIF_RAM_START);
    }
    if (direction == OS_READ) {
        osInvalDCache(dram_address, PIF_RAM_SIZE);
    }
    return 0;
}
