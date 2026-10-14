#include "ultra.h"

#define PI_DRAM_ADDR_REG 0xA4600000
#define PI_CART_ADDR_REG 0xA4600004
#define PI_RD_LEN_REG 0xA4600008
#define PI_WR_LEN_REG 0xA460000C
#define PI_STATUS_REG 0xA4600010
#define PI_STATUS_BUSY 3

extern u32 D_80000308;
extern u32 osVirtualToPhysical(void *);

s32 osPiRawStartDma(s32 direction, u32 device_address, void *dram_address, u32 size)
{
    register u32 status;

    while ((status = IO_READ(PI_STATUS_REG)) & PI_STATUS_BUSY) {
    }
    IO_WRITE(PI_DRAM_ADDR_REG, osVirtualToPhysical(dram_address));
    IO_WRITE(PI_CART_ADDR_REG, (D_80000308 | device_address) & 0x1FFFFFFF);
    switch (direction) {
    case OS_READ:
        IO_WRITE(PI_WR_LEN_REG, size - 1);
        break;
    case OS_WRITE:
        IO_WRITE(PI_RD_LEN_REG, size - 1);
        break;
    default:
        return -1;
    }
    return 0;
}
