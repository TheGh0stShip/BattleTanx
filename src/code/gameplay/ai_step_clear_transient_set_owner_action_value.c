#include "ai_play_stack.h"

extern void ai_push_param(AiActionContext *context, f32 value) __asm__("func_800E9A00");
extern s32 ai_clear_member_transient_state(AiActionContext *context) __asm__("func_800E6BF0");
extern s32 ai_set_owner_action_value_from_param(AiActionContext *context) __asm__("func_800E7064");
extern s32 ai_clear_action_params(AiActionContext *context) __asm__("func_800E99D4");

s32 ai_step_clear_transient_set_owner_action_value(AiActionContext *context) __asm__("func_800EABFC");

s32 ai_step_clear_transient_set_owner_action_value(AiActionContext *context)
{
    ai_clear_member_transient_state(context);
    ai_push_param(context, 0.2f);
    ai_set_owner_action_value_from_param(context);
    ai_clear_action_params(context);
    return -1;
}
