#include "types.h"

s32 __osSpDeviceBusy(void) {
    register u32 status = *(volatile u32*)0xA4040010;
    if (status & 0x1C) {
        return 1;
    }
    return 0;
}
