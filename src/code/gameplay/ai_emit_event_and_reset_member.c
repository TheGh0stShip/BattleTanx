#include "ai_action_internal.h"

s32 ai_action_emit_event_and_reset_member(AiActionContext *context) __asm__("func_800EB440");

s32 ai_action_emit_event_and_reset_member(AiActionContext *context)
{
    ai_emit_owner_event_1003(context);
    ai_reset_controlled_member(context);
    ai_update_member_link(context);
    return -1;
}
