#include "types.h"

typedef struct RuntimeTimerSource {
    u8 pad00[8];
    u32 startTime;
    u8 pad0C[12];
} RuntimeTimerSource;

typedef struct RuntimeState {
    u8 pad00[4];
    u32 currentTime;
    u8 pad08[0x88];
    RuntimeTimerSource sources[2];
    u8 padC0[0x10];
    u16 sourceIndex;
    u8 padD2[6];
    u8 runtimeRecord[0x30];
} RuntimeState;

extern RuntimeState *gRuntimeState __asm__("D_801257C8");

s32 runtime_record_timer_expired(void) __asm__("func_8007DBC4");

s32 runtime_record_timer_expired(void)
{
    RuntimeTimerSource *record;
    RuntimeState *runtime;
    s32 result = 0;

    record = &gRuntimeState->sources[gRuntimeState->sourceIndex];
    runtime = (RuntimeState *)((u8 *)gRuntimeState + 0xD8);
    if (runtime->currentTime > record->startTime + 0x5C00) {
        result = 1;
    }
    return result;
}
