#include "types.h"

extern u8 D_80152F90[];
extern s32 D_80125764;
extern void func_801193E0(void *queue, s32 message, s32 flags);

s32 wait_for_worker_message(void) __asm__("func_800795B0");

s32 wait_for_worker_message(void)
{
    func_801193E0(D_80152F90, 1, 0);
    return D_80125764;
}
