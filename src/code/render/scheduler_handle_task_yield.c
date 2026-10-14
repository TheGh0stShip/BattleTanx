#include "types.h"

#ifndef NULL
#define NULL 0
#endif

typedef struct Scheduler {
    u8 pad000[0x1F4];
    u16 flags;
    u8 pad1F6[6];
    s32 pendingRequest;
    void *currentTask;
    void *pendingTask;
} Scheduler;

extern void scheduler_start_next_task(Scheduler *scheduler) __asm__("func_800794C8");
extern void submit_worker_message(void) __asm__("func_800795E4");
extern s32 func_8011CDFC(void *task);
extern s32 func_8011CF8C(void *task);
extern s32 func_8011D100(void *task);
extern s32 func_80122720(void);

void scheduler_handle_task_yield(Scheduler *scheduler) __asm__("func_800792C8");

void scheduler_handle_task_yield(Scheduler *scheduler)
{
    void *task;
    u16 flags;

    flags = scheduler->flags;
    if (flags & 2) {
        scheduler->flags = flags & 0xFFFD;
        if (func_8011D100(scheduler->pendingTask) != 0) {
            scheduler->flags = scheduler->flags | 4;
        }
        func_80122720();
        func_8011CDFC(scheduler->currentTask);
        func_8011CF8C(scheduler->currentTask);
        scheduler->flags = scheduler->flags | 1;
        return;
    }
    if (scheduler->currentTask == NULL) {
        scheduler->flags = 0;
        return;
    }
    submit_worker_message();
    scheduler->currentTask = NULL;
    if (scheduler->flags & 4) {
        task = scheduler->pendingTask;
        if (task == NULL) {
            scheduler->flags = 0;
            return;
        }
        func_8011CDFC(task);
        func_8011CF8C(scheduler->pendingTask);
        if (scheduler->flags & 8) {
            scheduler->pendingTask = NULL;
        }
        scheduler->flags = 1;
        return;
    }
    if (scheduler->pendingTask == NULL && scheduler->pendingRequest == 1) {
        scheduler_start_next_task(scheduler);
        return;
    }
    scheduler->flags = 0;
}
