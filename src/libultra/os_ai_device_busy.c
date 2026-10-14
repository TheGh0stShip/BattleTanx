#include "types.h"

s32 __osAiDeviceBusy(void) {
    register u32 status = *(volatile u32*)0xA450000C;
    if (status & 0x80000000) {
        return 1;
    }
    return 0;
}
