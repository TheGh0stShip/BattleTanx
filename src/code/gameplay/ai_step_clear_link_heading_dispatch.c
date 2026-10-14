#include "ai_play_stack.h"

extern void ai_push_param(AiActionContext *context, f32 value) __asm__("func_800E9A00");
extern s32 ai_clear_linked_owner_value(AiActionContext *context) __asm__("func_800E73A4");
extern s32 func_800E75D4(AiActionContext *context);
extern s32 ai_clear_action_params(AiActionContext *context) __asm__("func_800E99D4");
extern s32 dispatch_context_action(AiActionContext *context) __asm__("func_800E69A4");
extern s32 ai_reset_owner_state(AiActionContext *context) __asm__("func_800E6C80");
extern s32 func_800E73E0(AiActionContext *context);

s32 ai_step_clear_link_heading_dispatch(AiActionContext *context) __asm__("func_800EBAE0");

s32 ai_step_clear_link_heading_dispatch(AiActionContext *context)
{
    ai_clear_linked_owner_value(context);
    ai_push_param(context, 0.0f);
    func_800E75D4(context);
    ai_clear_action_params(context);
    dispatch_context_action(context);
    ai_reset_owner_state(context);
    ai_push_param(context, 0.39996f);
    func_800E73E0(context);
    ai_clear_action_params(context);
    return -1;
}
