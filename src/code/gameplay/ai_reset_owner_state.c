#include "ai_action_helpers.h"

extern void reset_owner_state(void *owner) __asm__("func_800E5F30");

s32 ai_reset_owner_state(AiActionContext *context) __asm__("func_800E6C80");

s32 ai_reset_owner_state(AiActionContext *context)
{
    reset_owner_state(context->owner);
    return -1;
}
