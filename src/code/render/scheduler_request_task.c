#include "types.h"

#ifndef NULL
#define NULL 0
#endif

s32 func_800794C8();

void scheduler_request_task(void *arg0) __asm__("func_80079474");

void scheduler_request_task(void *arg0) {
    if (((*(s32 *)((s8 *)(arg0) + (0x204))) != 0) || ((*(u16 *)((s8 *)(arg0) + (0x1F4))) != 0)) {
        (*(s32 *)((s8 *)(arg0) + (0x1FC))) = 1;
        return;
    }
    func_800794C8();
}
