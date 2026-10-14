#include "types.h"

extern u8 D_802DF5D0[];
extern void func_801193E0(void *queue, void *message, s32 flags);

void submit_empty_io_request(void) __asm__("func_800A8E9C");

void submit_empty_io_request(void)
{
    s32 message = 0;
    func_801193E0(D_802DF5D0, &message, 0);
}
