#include "ai_action_helpers.h"

extern void release_target(u16 targetId) __asm__("func_800E4A18");

s32 ai_release_target(AiActionContext *context) __asm__("func_800E6C5C");

s32 ai_release_target(AiActionContext *context)
{
    release_target(context->targetId);
    return -1;
}
