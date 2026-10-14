#include "types.h"

extern void *D_80152A10;
extern u8 D_801B4A28[];
extern s32 D_80125764;
extern void func_801193E0(void *queue, void *message, s32 flags);

void submit_worker_message(void) __asm__("func_800795E4");

void submit_worker_message(void)
{
    func_801193E0(D_801B4A28, D_80152A10, 1);
    D_80125764 = 0;
}
