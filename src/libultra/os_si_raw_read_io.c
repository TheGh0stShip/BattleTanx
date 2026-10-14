#include "ultra.h"

extern s32 __osSiDeviceBusy(void);

s32 __osSiRawReadIo(u32 device_address, u32 *value)
{
    if (__osSiDeviceBusy()) {
        return -1;
    }
    *value = IO_READ(PHYS_TO_K1(device_address));
    return 0;
}
