#include "ai_play_stack.h"

extern void ai_push_param(AiActionContext *context, f32 value) __asm__("func_800E9A00");
extern s32 store_action_float_as_uint(AiActionContext *context) __asm__("func_800E6C14");
extern s32 ai_clear_action_params(AiActionContext *context) __asm__("func_800E99D4");
extern s32 ai_select_member_plays(AiActionContext *context) __asm__("func_800E6FD8");

s32 ai_step_select_member_plays_w3_a(AiActionContext *context) __asm__("func_800EB71C");

s32 ai_step_select_member_plays_w3_a(AiActionContext *context)
{
    ai_push_param(context, 3.0f);
    store_action_float_as_uint(context);
    ai_clear_action_params(context);
    ai_select_member_plays(context);
    return -1;
}
