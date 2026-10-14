#include "ai_action_internal.h"

s32 ai_action_set_heading_and_reset_member_alt(AiActionContext *context) __asm__("func_800EC084");

s32 ai_action_set_heading_and_reset_member_alt(AiActionContext *context)
{
    ai_push_param(context, 0.0f);
    ai_set_member_heading_from_param(context);
    clear_word_pair(context);
    ai_reset_controlled_member(context);
    ai_clear_member_action_byte(context);
    return -1;
}
