#include "ai_action_internal.h"

s32 ai_action_resolve_target_and_set_owner_value(AiActionContext *context) __asm__("func_800EAC80");

s32 ai_action_resolve_target_and_set_owner_value(AiActionContext *context)
{
    ai_resolve_member_target(context);
    ai_set_owner_action_value_from_param(context);
    return -1;
}
