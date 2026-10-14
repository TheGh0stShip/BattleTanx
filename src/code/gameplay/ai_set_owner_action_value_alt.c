#include "ai_action_internal.h"

s32 ai_action_set_owner_action_value_alt(AiActionContext *context) __asm__("func_800EBE6C");

s32 ai_action_set_owner_action_value_alt(AiActionContext *context)
{
    ai_push_param(context, 0.0f);
    ai_set_owner_action_value_from_param(context);
    clear_word_pair(context);
    return -1;
}
