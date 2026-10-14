#include "ai_play_stack.h"

extern void ai_push_param(AiActionContext *context, f32 value) __asm__("func_800E9A00");
extern s32 ai_invert_controller_flag(AiActionContext *context) __asm__("func_800E70C4");
extern s32 ai_schedule_owner_timer(AiActionContext *context) __asm__("func_800E70DC");
extern s32 ai_clear_action_params(AiActionContext *context) __asm__("func_800E99D4");

s32 ai_step_invert_flag_schedule_timer(AiActionContext *context) __asm__("func_800EBED4");

s32 ai_step_invert_flag_schedule_timer(AiActionContext *context)
{
    ai_invert_controller_flag(context);
    ai_push_param(context, 2.0f);
    ai_push_param(context, 10.0f);
    ai_schedule_owner_timer(context);
    ai_clear_action_params(context);
    return -1;
}
