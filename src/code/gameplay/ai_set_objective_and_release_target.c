#include "ai_action_internal.h"

s32 ai_action_set_objective_and_release_target(AiActionContext *context) __asm__("func_800EB920");

s32 ai_action_set_objective_and_release_target(AiActionContext *context)
{
    ai_push_param(context, 0.0f);
    ai_set_owner_objective_from_param(context);
    clear_word_pair(context);
    ai_release_action_target(context);
    return -1;
}
