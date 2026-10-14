#include "types.h"

extern void osCreateMesgQueue(u8 *queue, u8 *messages, s32 count) __asm__("func_80111510");
extern void osCreateThread(u8 *thread, s32 id, void (*entry)(void), void *arg, u8 *stackTop, s32 priority)
    __asm__("func_80111540");
extern void osSetEventMesg(s32 event, u8 *queue, s32 message) __asm__("func_8011BA10");
extern void osStartThread(u8 *thread) __asm__("func_8011D1A0");
extern void osViBlack(s32 active) __asm__("func_801219B0");
extern void osCreateViManager(s32 priority) __asm__("func_80121BA0");
extern void osViSetEvent(u8 *queue, s32 message, u8 retraceCount) __asm__("func_80122050");
extern void osViSetMode(u8 *mode) __asm__("func_801220C0");
extern void osViSetSpecialFeatures(s32 features) __asm__("func_80122130");
extern void initialize_runtime_record_1e8(u8 *record) __asm__("func_8007902C");
extern void graphics_thread_entry(void) __asm__("func_80078F70");

extern u8 gViModeTable[][0x50] __asm__("D_801462A0");
extern u8 gGraphicsMessageQueue[] __asm__("D_8014E0D0");
extern s16 gGraphicsRecordValue __asm__("D_8014E2BC");
extern u8 gGraphicsThreadStackTop[] __asm__("D_801502E0");

void start_graphics_thread(s32 id, s32 priority, u8 viMode, u8 retraceCount, s32 recordValue)
    __asm__("func_80078E30");

void start_graphics_thread(s32 id, s32 priority, u8 viMode, u8 retraceCount, s32 recordValue)
{
    osCreateMesgQueue(gGraphicsMessageQueue, gGraphicsMessageQueue + 0x18, 8);
    osCreateViManager(0xFE);
    osViSetMode(gViModeTable[viMode]);
    osViSetSpecialFeatures(0x42);
    osViBlack(1);
    osSetEventMesg(4, gGraphicsMessageQueue, 0x29B);
    osSetEventMesg(9, gGraphicsMessageQueue, 0x29C);
    osSetEventMesg(0xE, gGraphicsMessageQueue, 0x29E);
    osViSetEvent(gGraphicsMessageQueue, 0x29A, retraceCount);
    gGraphicsRecordValue = recordValue;
    initialize_runtime_record_1e8(gGraphicsMessageQueue);
    osCreateThread(gGraphicsMessageQueue + 0x38, id, graphics_thread_entry, gGraphicsMessageQueue,
                   gGraphicsThreadStackTop, priority);
    osStartThread(gGraphicsMessageQueue + 0x38);
}
