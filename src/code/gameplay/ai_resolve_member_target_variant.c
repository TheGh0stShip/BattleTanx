#include "ai_action_internal.h"

s32 ai_action_resolve_member_target_variant(AiActionContext *context) __asm__("func_800EB1A0");

s32 ai_action_resolve_member_target_variant(AiActionContext *context)
{
    ai_resolve_member_target(context);
    return -1;
}
