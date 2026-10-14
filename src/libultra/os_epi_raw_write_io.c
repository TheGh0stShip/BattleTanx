#include "ultra.h"

#define PI_STATUS_REG 0xA4600010
#define PI_STATUS_ERROR 0x4
#define PI_STATUS_IO_BUSY 0x2
#define PI_STATUS_DMA_BUSY 0x1

s32 osEPiRawWriteIo(OSPiHandle *handle, u32 devAddr, u32 data)
{
    register u32 stat;

    while ((stat = IO_READ(PI_STATUS_REG)) & (PI_STATUS_IO_BUSY | PI_STATUS_DMA_BUSY)) {
    }
    IO_WRITE(PHYS_TO_K1(handle->baseAddress | devAddr), data);
    return 0;
}
