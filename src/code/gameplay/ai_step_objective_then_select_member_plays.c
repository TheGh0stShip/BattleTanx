#include "ai_play_stack.h"

extern void ai_push_param(AiActionContext *context, f32 value) __asm__("func_800E9A00");
extern s32 ai_set_owner_objective_from_param(AiActionContext *context) __asm__("func_800E6FF8");
extern s32 ai_clear_action_params(AiActionContext *context) __asm__("func_800E99D4");
extern s32 store_action_float_as_uint(AiActionContext *context) __asm__("func_800E6C14");
extern s32 ai_select_member_plays(AiActionContext *context) __asm__("func_800E6FD8");
extern s32 ai_release_target(AiActionContext *context) __asm__("func_800E6C5C");

s32 ai_step_objective_then_select_member_plays(AiActionContext *context) __asm__("func_800EB7AC");

s32 ai_step_objective_then_select_member_plays(AiActionContext *context)
{
    ai_push_param(context, 255.0f);
    ai_set_owner_objective_from_param(context);
    ai_clear_action_params(context);
    ai_push_param(context, 1.0f);
    store_action_float_as_uint(context);
    ai_clear_action_params(context);
    ai_select_member_plays(context);
    ai_release_target(context);
    return -1;
}
