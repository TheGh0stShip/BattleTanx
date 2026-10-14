#include "ai_action_helpers.h"

extern void set_owner_target(void *owner, s32 target) __asm__("func_80099D90");

s32 ai_clear_owner_target(AiActionContext *context) __asm__("func_800E72FC");

s32 ai_clear_owner_target(AiActionContext *context)
{
    set_owner_target(context->owner, 0);
    return -1;
}
