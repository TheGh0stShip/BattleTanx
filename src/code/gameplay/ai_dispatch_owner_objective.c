#include "ai_play_stack.h"

typedef struct AiObjectiveOwner {
    u8 pad000[0x1A8];
    u16 objectiveId;
} AiObjectiveOwner;

extern void func_800E3980(void *memberState, s16 memberId, u16 parameter, s32 enabled);

s32 ai_dispatch_owner_objective(AiActionContext *context) __asm__("func_800E6970");

s32 ai_dispatch_owner_objective(AiActionContext *context)
{
    func_800E3980(context->memberState, context->memberId,
                  ((AiObjectiveOwner *)context->owner)->objectiveId, 1);
    return -1;
}
