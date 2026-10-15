#ifndef AI_ACTION_POLICY_H
#define AI_ACTION_POLICY_H

#include "types.h"

typedef struct AiActionContext AiActionContext;
typedef struct AiActionPolicy AiActionPolicy;

extern s32 ai_select_weighted_action(AiActionContext *context, AiActionPolicy *policy)
    __asm__("func_800EA93C");
extern void ai_push_param(AiActionContext *context, f32 value) __asm__("func_800E9A00");
extern void ai_prepare_metric_6970(AiActionContext *context) __asm__("func_800E6970");
extern void ai_prepare_metric_6bf0(AiActionContext *context) __asm__("func_800E6BF0");
extern void ai_prepare_metric_6c14(AiActionContext *context) __asm__("func_800E6C14");
extern void ai_prepare_metric_6c5c(AiActionContext *context) __asm__("func_800E6C5C");
extern s32 ai_select_owner_target_member(AiActionContext *context) __asm__("func_800E6D58");
extern void ai_prepare_metric_6fd8(AiActionContext *context) __asm__("func_800E6FD8");
extern void ai_prepare_metric_75d4(AiActionContext *context) __asm__("func_800E75D4");
extern void ai_prepare_metric_76d0(AiActionContext *context) __asm__("func_800E76D0");
extern void ai_finalize_action_metrics(AiActionContext *context) __asm__("func_800E99D4");

#endif
