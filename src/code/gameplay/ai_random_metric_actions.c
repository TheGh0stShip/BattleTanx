#include "types.h"

typedef struct AiActionContext AiActionContext;

extern s32 ai_update_random_metric(AiActionContext *context, u32 metric) __asm__("func_800E7168");

s32 ai_action_update_random_metric_8(AiActionContext *context) __asm__("func_800E7320");
s32 ai_action_update_random_metric_3(AiActionContext *context) __asm__("func_800E7340");
s32 ai_action_update_random_metric_2(AiActionContext *context) __asm__("func_800E7360");

s32 ai_action_update_random_metric_8(AiActionContext *context)
{
    ai_update_random_metric(context, 8);
    return -1;
}

s32 ai_action_update_random_metric_3(AiActionContext *context)
{
    ai_update_random_metric(context, 3);
    return -1;
}

s32 ai_action_update_random_metric_2(AiActionContext *context)
{
    ai_update_random_metric(context, 2);
    return -1;
}
