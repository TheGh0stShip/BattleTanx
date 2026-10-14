#include "types.h"

typedef struct Scheduler {
    u8 pad000[0x1E8];
    s32 retraceCount;
    u16 waitFrames;
    u16 framesSinceTask;
    u16 frameCounter;
    u8 pad1F2[2];
    u16 taskState;
    u8 pad1F6[2];
    s32 pendingSwap;
    s32 value1FC;
    void *currentTask;
    void *value204;
} Scheduler;

extern void submit_empty_io_request(void) __asm__("func_800A8E9C");
extern void stop_all_rumble_paks(void) __asm__("func_800A9010");
extern void scheduler_start_next_task(Scheduler *sched) __asm__("func_800794C8");
extern void scheduler_swap_framebuffer(Scheduler *sched) __asm__("func_80079530");
extern void *wait_for_worker_message(u16 frames) __asm__("func_800795B0");
extern void func_8007F070(s32 index, s32 value);
extern s32 func_8007F204(s32 index);
extern void func_8011CDFC(void *task);
extern void func_8011CF8C(void *task);
extern void func_8011D0E0(void);
extern s32 func_80121B60(void);
extern void func_80122720(void);

extern s32 gGraphicsThreadStopRequested __asm__("D_801502E0");
extern u16 D_80000400[];

void scheduler_handle_retrace(Scheduler *sched) __asm__("func_800790EC");

void scheduler_handle_retrace(Scheduler *sched)
{
    s32 stop;
    u32 i;
    s32 framebuffer;
    s32 swap;
    u16 frames;

    submit_empty_io_request();
    stop = gGraphicsThreadStopRequested;
    if (stop != 0) {
        gGraphicsThreadStopRequested = stop + 1;
        if (stop & 0x10) {
            for (i = 0; i < 0x38400; i++) {
                D_80000400[i] = (D_80000400[i] >> 1) & 0x7BDE;
            }
        }
        if ((gGraphicsThreadStopRequested & 0xF) == 0xF) {
            stop_all_rumble_paks();
        }
        return;
    }
    frames = sched->framesSinceTask + 1;
    sched->framesSinceTask = frames;
    sched->retraceCount++;
    if (frames >= sched->waitFrames && sched->currentTask == 0) {
        sched->currentTask = wait_for_worker_message(sched->waitFrames);
        if (sched->currentTask != 0) {
            if (sched->taskState != 0) {
                func_8011D0E0();
                sched->taskState |= 2;
            } else {
                func_80122720();
                func_8011CDFC(sched->currentTask);
                func_8011CF8C(sched->currentTask);
                sched->taskState = 1;
            }
            sched->framesSinceTask = 0;
        }
    }
    sched->frameCounter++;
    scheduler_swap_framebuffer(sched);
    framebuffer = func_8007F204(1);
    if (framebuffer != 0 && func_80121B60() == framebuffer) {
        func_8007F070(0, framebuffer);
        swap = sched->pendingSwap;
        if (swap == 1) {
            func_8007F070(1, func_8007F204(2));
            if (sched->taskState == 0 && sched->value1FC == swap) {
                scheduler_start_next_task(sched);
            } else {
                sched->value204 = 0;
            }
            sched->pendingSwap = 0;
        } else {
            func_8007F070(1, 0);
        }
    }
}
