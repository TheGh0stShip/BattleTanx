#include "types.h"

typedef struct RuntimeDataState {
    s32 value;
    s32 offset;
} RuntimeDataState;

extern RuntimeDataState *gRuntimeDataState __asm__("D_80135834");

void advance_runtime_data_offset(s32 amount) __asm__("func_800E0954");

void advance_runtime_data_offset(s32 amount)
{
    RuntimeDataState *state = gRuntimeDataState;

    state->offset = (state->offset + (state->offset & 7)) +
                    ((amount & 7) + amount);
}
