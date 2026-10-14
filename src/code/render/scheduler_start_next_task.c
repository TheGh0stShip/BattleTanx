#include "types.h"

#ifndef NULL
#define NULL 0
#endif

void *func_8007F040();
s32 func_8007F070(s32, s32);
s32 func_8011CDFC(void *);
s32 func_8011CF8C(void *);

void scheduler_start_next_task(void *arg0) __asm__("func_800794C8");

void scheduler_start_next_task(void *arg0) {
    void *temp_v0;

    temp_v0 = func_8007F040();
    (*(void **)((s8 *)(arg0) + (0x204))) = temp_v0;
    func_8007F070(2, (*(s32 *)((s8 *)(temp_v0) + (0x40))));
    func_8007F070(3, 0);
    func_8011CDFC((*(void **)((s8 *)(arg0) + (0x204))));
    func_8011CF8C((*(void **)((s8 *)(arg0) + (0x204))));
    (*(s32 *)((s8 *)(arg0) + (0x1FC))) = 0;
    (*(s16 *)((s8 *)(arg0) + (0x1F4))) = 1;
}
