#include "ai_play_stack.h"

extern void ai_push_param(AiActionContext *context, f32 value) __asm__("func_800E9A00");
extern f32 D_800749A0;
extern f32 D_800749A4;
extern s32 func_800E7490(AiActionContext *context);
extern s32 ai_clear_action_params(AiActionContext *context) __asm__("func_800E99D4");
extern s32 func_800E7628(AiActionContext *context);

s32 ai_step_apply_weighted_metrics(AiActionContext *context) __asm__("func_800EAD9C");

s32 ai_step_apply_weighted_metrics(AiActionContext *context)
{
    f32 weight0;
    f32 weight1;

    weight0 = D_800749A0;
    weight1 = D_800749A4;
    ai_push_param(context, weight0);
    ai_push_param(context, weight1);
    func_800E7490(context);
    ai_clear_action_params(context);
    ai_push_param(context, weight0);
    ai_push_param(context, weight1);
    func_800E7628(context);
    ai_clear_action_params(context);
    return -1;
}
