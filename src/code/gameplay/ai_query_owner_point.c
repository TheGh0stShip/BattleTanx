#include "ai_play_stack.h"

typedef struct AiOwnerPoint {
    u8 pad000[0x144];
    u8 point;
} AiOwnerPoint;

extern void func_800E3A38(void *memberState, void *point, s32 *result);

s32 ai_query_owner_point(AiActionContext *context) __asm__("func_800E6A78");

s32 ai_query_owner_point(AiActionContext *context)
{
    s32 result[2];

    result[1] = 0;
    result[0] = 0;
    func_800E3A38(context->memberState, &((AiOwnerPoint *)context->owner)->point, result);
    return -1;
}
