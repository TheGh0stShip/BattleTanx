#include "ai_play_stack.h"

extern void ai_push_param(AiActionContext *context, f32 value) __asm__("func_800E9A00");
extern s32 ai_action_update_random_metric_8(AiActionContext *context) __asm__("func_800E7320");
extern s32 ai_clear_action_params(AiActionContext *context) __asm__("func_800E99D4");
extern s32 ai_action_update_random_metric_2(AiActionContext *context) __asm__("func_800E7360");
extern s32 ai_enable_member_flag_2ba(AiActionContext *context) __asm__("func_800E7380");
extern s32 ai_dispatch_owner_position(AiActionContext *context) __asm__("func_800E6BBC");

s32 ai_step_random_metrics_weighted(AiActionContext *context) __asm__("func_800EB5E8");

s32 ai_step_random_metrics_weighted(AiActionContext *context)
{
    ai_push_param(context, 0.5f);
    ai_action_update_random_metric_8(context);
    ai_clear_action_params(context);
    ai_action_update_random_metric_2(context);
    ai_enable_member_flag_2ba(context);
    ai_dispatch_owner_position(context);
    return -1;
}
