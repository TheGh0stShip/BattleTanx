#include "ai_action_internal.h"

s32 ai_action_resolve_member_target(AiActionContext *context) __asm__("func_800EC03C");

s32 ai_action_resolve_member_target(AiActionContext *context)
{
    ai_resolve_member_target(context);
    return -1;
}
