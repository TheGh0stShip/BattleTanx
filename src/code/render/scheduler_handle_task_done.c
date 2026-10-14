#include "types.h"

#ifndef NULL
#define NULL 0
#endif

s32 func_800794C8(void *);
s32 func_80079530(void *);
s32 func_8007F070(s32, s32);
s32 func_8007F204(s32);

void scheduler_handle_task_done(void *arg0) __asm__("func_800793D0");

void scheduler_handle_task_done(void *arg0) {
    u16 temp_v1;

    if (func_8007F204(1) == 0) {
        func_8007F070(1, (*(s32 *)((s8 *)((*(void **)((s8 *)(arg0) + (0x204)))) + (0x40))));
        func_8007F070(2, 0);
        if (((*(u16 *)((s8 *)(arg0) + (0x1F4))) == 0) && ((*(s32 *)((s8 *)(arg0) + (0x1FC))) == 1)) {
            func_800794C8(arg0);
        } else {
            temp_v1 = (*(u16 *)((s8 *)(arg0) + (0x1F4)));
            if (temp_v1 & 4) {
                (*(u16 *)((s8 *)(arg0) + (0x1F4))) = (u16) (temp_v1 | 8);
            } else {
                (*(void **)((s8 *)(arg0) + (0x204))) = NULL;
            }
        }
    } else {
        (*(s32 *)((s8 *)(arg0) + (0x1F8))) = 1;
    }
    func_80079530(arg0);
}
