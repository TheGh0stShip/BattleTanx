#include "types.h"

typedef struct AiMemberOrderContext {
    u8 pad00[0xC];
    s32 member;
    u8 pad10[8];
    s16 order;
} AiMemberOrderContext;

extern s16 ai_get_current_team(void) __asm__("func_800E3F90");
extern void ai_issue_member_order(s32, s16, s16) __asm__("func_800E3B38");

s32 ai_dispatch_member_order(AiMemberOrderContext *context) __asm__("func_800E6A30");
s32 ai_member_order_noop(void) __asm__("func_800E6A70");

s32 ai_dispatch_member_order(AiMemberOrderContext *context)
{
    ai_issue_member_order(context->member, context->order, ai_get_current_team());
    return -1;
}

s32 ai_member_order_noop(void)
{
    return -1;
}
