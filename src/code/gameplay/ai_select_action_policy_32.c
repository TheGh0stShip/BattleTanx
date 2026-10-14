#include "ai_action_policy.h"

extern AiActionPolicy D_801371D0;

s32 ai_select_action_policy_32(AiActionContext *context) __asm__("func_800EBC1C");

s32 ai_select_action_policy_32(AiActionContext *context)
{
    return ai_select_weighted_action(context, &D_801371D0);
}
