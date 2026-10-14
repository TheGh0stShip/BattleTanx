#include "ai_play_stack.h"

extern void ai_push_param(AiActionContext *context, f32 value) __asm__("func_800E9A00");
extern s32 func_800E7560(AiActionContext *context);
extern s32 ai_clear_action_params(AiActionContext *context) __asm__("func_800E99D4");
extern s32 func_800E7628(AiActionContext *context);

s32 ai_step_apply_metric_profile_b(AiActionContext *context) __asm__("func_800EAEA8");

s32 ai_step_apply_metric_profile_b(AiActionContext *context)
{
    ai_push_param(context, 0.0f);
    func_800E7560(context);
    ai_clear_action_params(context);
    ai_push_param(context, 0.1f);
    ai_push_param(context, 0.25f);
    func_800E7628(context);
    ai_clear_action_params(context);
    return -1;
}
