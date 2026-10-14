#include "ai_action_internal.h"

s32 ai_action_resolve_member_target_alt(AiActionContext *context) __asm__("func_800EB00C");

s32 ai_action_resolve_member_target_alt(AiActionContext *context)
{
    ai_resolve_member_target(context);
    return -1;
}
