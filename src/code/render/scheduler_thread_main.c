#include "types.h"

extern s32 osRecvMesg(void *queue, void **message, s32 flags) __asm__("func_80119240");
extern void scheduler_handle_retrace(void *scheduler) __asm__("func_800790EC");
extern void scheduler_handle_task_yield(void *scheduler) __asm__("func_800792C8");
extern void scheduler_handle_task_done(void *scheduler) __asm__("func_800793D0");
extern void scheduler_request_task(void *scheduler) __asm__("func_80079474");
extern void request_graphics_thread_stop(void *scheduler) __asm__("func_800794B4");

void scheduler_thread_main(void *scheduler) __asm__("func_80078F70");

void scheduler_thread_main(void *scheduler) {
    void *message;

    while (1) {
        osRecvMesg(scheduler, &message, 1);
        switch ((s32) message) {
            case 0x29A:
                scheduler_handle_retrace(scheduler);
                break;
            case 0x29B:
                scheduler_handle_task_yield(scheduler);
                break;
            case 0x29C:
                scheduler_handle_task_done(scheduler);
                break;
            case 0x29D:
                scheduler_request_task(scheduler);
                break;
            case 0x29E:
                request_graphics_thread_stop(scheduler);
                break;
        }
    }
}
