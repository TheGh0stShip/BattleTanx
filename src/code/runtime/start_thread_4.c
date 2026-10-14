#include "types.h"

extern void create_message_queue(void *queue, void *messages, s32 count) __asm__("func_80111510");
extern void create_thread(void *thread, s32 id, void (*entry)(void *), void *arg, void *stack, s32 priority)
    __asm__("func_80111540");
extern void thread_4_entry(void *arg) __asm__("func_8007A470");
extern u8 D_801529D8[];
extern u8 gThread4StackEnd[] __asm__("D_801529D8");
extern u8 D_801529F0[];
extern u8 D_80152A18[];
extern u8 D_80152A38[];
extern u8 D_80152F00[];
extern u8 D_80152F90[];
extern u8 D_801B4A28[];

void start_thread_4(s32 priority) __asm__("func_8007A3D8");

void start_thread_4(s32 priority)
{
    create_message_queue(D_801B4A28, D_80152A18, 8);
    create_message_queue(D_80152F90, D_801529F0, 8);
    create_message_queue(D_801529D8, D_80152F00, 0x20);
    create_thread(D_80152A38, 4, thread_4_entry, 0, gThread4StackEnd, priority);
}
