#include "ai_play_stack.h"

extern void ai_push_param(AiActionContext *context, f32 value) __asm__("func_800E9A00");
extern s32 func_800E75D4(AiActionContext *context);
extern s32 ai_clear_action_params(AiActionContext *context) __asm__("func_800E99D4");
extern s32 ai_reset_controlled_member(AiActionContext *context) __asm__("func_800E6AAC");
extern s32 ai_query_owner_point(AiActionContext *context) __asm__("func_800E6A78");
extern s32 ai_reset_owner_state(AiActionContext *context) __asm__("func_800E6C80");

s32 ai_step_heading_reset_member_query_point(AiActionContext *context) __asm__("func_800EB07C");

s32 ai_step_heading_reset_member_query_point(AiActionContext *context)
{
    ai_push_param(context, 0.5f);
    func_800E75D4(context);
    ai_clear_action_params(context);
    ai_push_param(context, 1.0f);
    ai_reset_controlled_member(context);
    ai_clear_action_params(context);
    ai_query_owner_point(context);
    ai_reset_owner_state(context);
    return -1;
}
