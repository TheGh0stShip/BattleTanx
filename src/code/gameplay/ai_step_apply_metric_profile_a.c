#include "ai_play_stack.h"

extern void ai_push_param(AiActionContext *context, f32 value) __asm__("func_800E9A00");
extern f32 D_800749A8;
extern s32 func_800E7560(AiActionContext *context);
extern s32 ai_clear_action_params(AiActionContext *context) __asm__("func_800E99D4");
extern s32 func_800E7628(AiActionContext *context);

s32 ai_step_apply_metric_profile_a(AiActionContext *context) __asm__("func_800EAE30");

s32 ai_step_apply_metric_profile_a(AiActionContext *context)
{
    f32 weight0;

    weight0 = D_800749A8;
    ai_push_param(context, weight0);
    func_800E7560(context);
    ai_clear_action_params(context);
    ai_push_param(context, weight0);
    ai_push_param(context, 0.5f);
    func_800E7628(context);
    ai_clear_action_params(context);
    return -1;
}
