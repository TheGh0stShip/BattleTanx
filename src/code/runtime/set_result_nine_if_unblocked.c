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

void set_result_nine_if_unblocked(void *arg0, ReadinessContext *context, s32 inhibited, void *arg3, s32 *result)
    __asm__("func_800A7614");

void set_result_nine_if_unblocked(void *arg0, ReadinessContext *context, s32 inhibited, void *arg3, s32 *result)
{
    if (inhibited == 0 && context->blocked == 0 && context->state->ready == 0) {
        *result = 9;
    }
}
