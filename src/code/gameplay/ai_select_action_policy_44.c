#include "ai_action_policy.h"

extern AiActionPolicy D_801375A0;

s32 ai_select_action_policy_44(AiActionContext *context) __asm__("func_800EBFA4");

s32 ai_select_action_policy_44(AiActionContext *context)
{
    return ai_select_weighted_action(context, &D_801375A0);
}
