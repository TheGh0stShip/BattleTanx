#include "types.h"

extern void start_worker_thread(s32 threadId) __asm__("func_8007A3D8");

void start_worker_thread_20(void) __asm__("func_8007961C");

void start_worker_thread_20(void)
{
    start_worker_thread(0x14);
}
