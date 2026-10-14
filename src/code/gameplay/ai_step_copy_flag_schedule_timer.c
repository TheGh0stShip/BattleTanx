#include "ai_play_stack.h"

extern void ai_push_param(AiActionContext *context, f32 value) __asm__("func_800E9A00");
extern s32 ai_copy_controller_flag(AiActionContext *context) __asm__("func_800E70B0");
extern s32 ai_schedule_owner_timer(AiActionContext *context) __asm__("func_800E70DC");
extern s32 ai_clear_action_params(AiActionContext *context) __asm__("func_800E99D4");

s32 ai_step_copy_flag_schedule_timer(AiActionContext *context) __asm__("func_800EBF50");

s32 ai_step_copy_flag_schedule_timer(AiActionContext *context)
{
    ai_copy_controller_flag(context);
    ai_push_param(context, 2.0f);
    ai_push_param(context, 10.0f);
    ai_schedule_owner_timer(context);
    ai_clear_action_params(context);
    return -1;
}
