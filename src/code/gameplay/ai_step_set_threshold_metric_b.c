#include "ai_play_stack.h"

extern void ai_push_param(AiActionContext *context, f32 value) __asm__("func_800E9A00");
extern s32 ai_set_member_threshold_minus_one(AiActionContext *context) __asm__("func_800E7458");
extern s32 func_800E7628(AiActionContext *context);
extern s32 ai_clear_action_params(AiActionContext *context) __asm__("func_800E99D4");

s32 ai_step_set_threshold_metric_b(AiActionContext *context) __asm__("func_800EAF6C");

s32 ai_step_set_threshold_metric_b(AiActionContext *context)
{
    ai_set_member_threshold_minus_one(context);
    ai_push_param(context, 0.75f);
    ai_push_param(context, 0.9f);
    func_800E7628(context);
    ai_clear_action_params(context);
    return -1;
}
