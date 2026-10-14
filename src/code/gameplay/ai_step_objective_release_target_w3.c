#include "ai_play_stack.h"

extern void ai_push_param(AiActionContext *context, f32 value) __asm__("func_800E9A00");
extern s32 ai_set_owner_objective_from_param(AiActionContext *context) __asm__("func_800E6FF8");
extern s32 ai_clear_action_params(AiActionContext *context) __asm__("func_800E99D4");
extern s32 ai_release_target(AiActionContext *context) __asm__("func_800E6C5C");

s32 ai_step_objective_release_target_w3(AiActionContext *context) __asm__("func_800EBA70");

s32 ai_step_objective_release_target_w3(AiActionContext *context)
{
    ai_push_param(context, 3.0f);
    ai_set_owner_objective_from_param(context);
    ai_clear_action_params(context);
    ai_release_target(context);
    return -1;
}
