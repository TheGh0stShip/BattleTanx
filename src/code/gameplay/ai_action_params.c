#include "types.h"

typedef struct AiActionParams {
    u8 pad00[0x30];
    s32 values[4];
    s32 readIndex;
    s32 count;
} AiActionParams;

void ai_clear_action_params(AiActionParams *params) __asm__("func_800E99D4");
void ai_append_action_param(AiActionParams *params, s32 value) __asm__("func_800E99E0");

void ai_clear_action_params(AiActionParams *params)
{
    params->readIndex = 0;
    params->count = 0;
}

void ai_append_action_param(AiActionParams *params, s32 value)
{
    params->values[params->count] = value;
    params->count++;
}
