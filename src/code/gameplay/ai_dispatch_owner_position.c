#include "ai_play_stack.h"

typedef struct AiObjectiveOwner {
    u8 pad000[0x1A8];
    u16 objectiveId;
} AiObjectiveOwner;

extern void func_800E3980(void *position, s16 memberId, u16 parameter, s32 enabled);

s32 ai_dispatch_owner_position(AiActionContext *context) __asm__("func_800E6BBC");

s32 ai_dispatch_owner_position(AiActionContext *context)
{
    func_800E3980((u8 *)context->memberState + 0x18, context->memberId,
                  ((AiObjectiveOwner *)context->owner)->objectiveId, 0);
    return -1;
}
