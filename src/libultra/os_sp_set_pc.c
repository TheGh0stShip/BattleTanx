#include "types.h"

s32 __osSpSetPc(u32 pc) {
    register u32 status = *(volatile u32*)0xA4040010;
    if (!(status & 1)) {
        return -1;
    }
    *(volatile u32*)0xA4080000 = pc;
    return 0;
}
