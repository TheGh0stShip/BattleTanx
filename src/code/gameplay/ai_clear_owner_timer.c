#include "ai_action_internal.h"

s32 ai_action_clear_owner_timer(AiActionContext *context) __asm__("func_800EBB80");

s32 ai_action_clear_owner_timer(AiActionContext *context)
{
    ai_clear_owner_action_timer(context);
    ai_update_owner_after_timer_clear(context);
    return -1;
}
