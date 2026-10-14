#include "os_thread.h"

#define OS_IM_ALL 0x003FFF01
#define RCP_IMASK 0x003F0000
#define RCP_IMASKSHIFT 16
#define SR_IMASK 0x0000FF00
#define SR_EXL 0x00000002
#define SR_IE 0x00000001
#define FPCSR_FS 0x01000000
#define FPCSR_EV 0x00000800
#define OS_STATE_STOPPED 1

extern OSThread *D_801460FC;

extern u32 __osDisableInt(void);
extern void __osRestoreInt(u32);
extern void __osCleanupThread(void);

void osCreateThread(OSThread *thread, OSId id, void (*entry)(void *), void *arg,
                    void *stack, OSPri priority)
{
    register u32 save_mask;
    u32 interrupt_mask;

    thread->id = id;
    thread->priority = priority;
    thread->next = 0;
    thread->queue = 0;
    thread->context.pc = (u32)entry;
    thread->context.a0 = (s32)arg;
    thread->context.sp = (s64)(s32)stack - 16;
    thread->context.ra = (s32)__osCleanupThread;
    interrupt_mask = OS_IM_ALL;
    thread->context.sr = SR_IMASK | SR_EXL | SR_IE;
    thread->context.rcp = (interrupt_mask & RCP_IMASK) >> RCP_IMASKSHIFT;
    thread->context.fpcsr = FPCSR_FS | FPCSR_EV;
    thread->fp = 0;
    thread->state = OS_STATE_STOPPED;
    thread->flags = 0;

    save_mask = __osDisableInt();
    thread->tlnext = D_801460FC;
    D_801460FC = thread;
    __osRestoreInt(save_mask);
}
