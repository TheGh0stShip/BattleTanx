#include "ai_action_helpers.h"

extern void release_owner_resource(void *owner) __asm__("func_800E4494");

s32 ai_release_owner_resource(AiActionContext *context) __asm__("func_800E73BC");

s32 ai_release_owner_resource(AiActionContext *context)
{
    release_owner_resource(context->owner);
    return -1;
}
