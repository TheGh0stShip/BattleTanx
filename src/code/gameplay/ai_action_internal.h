#ifndef AI_ACTION_INTERNAL_H
#define AI_ACTION_INTERNAL_H

#include "types.h"

typedef struct AiActionContext AiActionContext;

extern s32 ai_assign_owner_objective(AiActionContext *context) __asm__("func_800E6970");
extern s32 ai_set_target_from_action(AiActionContext *context) __asm__("func_800E69A4");
extern s32 ai_reset_controlled_member(AiActionContext *context) __asm__("func_800E6AAC");
extern s32 ai_update_member_link(AiActionContext *context) __asm__("func_800E6B14");
extern s32 ai_resolve_member_target(AiActionContext *context) __asm__("func_800E6B3C");
extern s32 ai_reset_member_link_state(AiActionContext *context) __asm__("func_800E6BF0");
extern s32 ai_release_action_target(AiActionContext *context) __asm__("func_800E6C5C");
extern s32 ai_sync_owner_action(AiActionContext *context) __asm__("func_800E6C80");
extern s32 ai_emit_owner_event_1003(AiActionContext *context) __asm__("func_800E6FB0");
extern s32 ai_assign_squad_plays(void) __asm__("func_800E6FD8");
extern s32 ai_set_owner_objective_from_param(AiActionContext *context) __asm__("func_800E6FF8");
extern s32 ai_set_owner_action_value_from_param(AiActionContext *context) __asm__("func_800E7064");
extern s32 ai_copy_owner_behavior_flag(AiActionContext *context) __asm__("func_800E70B0");
extern s32 ai_invert_owner_behavior_flag(AiActionContext *context) __asm__("func_800E70C4");
extern s32 ai_clear_member_action_byte(AiActionContext *context) __asm__("func_800E7394");
extern s32 ai_update_owner_after_timer_clear(AiActionContext *context) __asm__("func_800E73BC");
extern s32 ai_clear_owner_action_timer(AiActionContext *context) __asm__("func_800E7448");
extern s32 ai_set_member_heading_from_param(AiActionContext *context) __asm__("func_800E75D4");
extern void ai_push_param(AiActionContext *context, f32 value) __asm__("func_800E9A00");
extern void clear_word_pair(void *owner) __asm__("func_800E99D4");

#endif
