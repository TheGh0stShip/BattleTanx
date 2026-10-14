#include "ultra.h"

extern s32 __osSiDeviceBusy(void);

s32 __osSiRawWriteIo(u32 device_address, u32 value)
{
    if (__osSiDeviceBusy()) {
        return -1;
    }
    IO_WRITE(PHYS_TO_K1(device_address), value);
    return 0;
}
