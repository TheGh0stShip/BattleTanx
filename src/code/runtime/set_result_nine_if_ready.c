#include "types.h"

typedef struct ReadinessState {
    u8 pad00[4];
    u8 ready;
} ReadinessState;

typedef struct ReadinessContext {
    u8 pad00[8];
    s32 blocked;
    ReadinessState *state;
} ReadinessContext;

void set_result_nine_if_ready(void *arg0, ReadinessContext *context, void *arg2, s32 *result)
    __asm__("func_800A75EC");

void set_result_nine_if_ready(void *arg0, ReadinessContext *context, void *arg2, s32 *result)
{
    if (context->blocked == 0 && context->state->ready == 0) {
        *result = 9;
    }
}
