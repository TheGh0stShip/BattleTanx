#include "ultra.h"

#define PI_STATUS_REG 0xA4600010
#define PI_STATUS_BUSY 3

extern u32 D_80000308;

s32 osPiRawReadIo(u32 device_address, u32 *value)
{
    register u32 status;

    while ((status = IO_READ(PI_STATUS_REG)) & PI_STATUS_BUSY) {
    }
    *value = IO_READ(PHYS_TO_K1(D_80000308 | device_address));
    return 0;
}
