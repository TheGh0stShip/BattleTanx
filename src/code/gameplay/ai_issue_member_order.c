#include "types.h"

typedef struct AiMemberOrder {
    s32 state;
    s32 value04;
    u8 pad08[0x8];
    void *targetUnit;
    s32 slotInfo;
} AiMemberOrder;

extern void *get_unit(s16 id) __asm__("func_800A03B8");
extern s32 ai_get_member_slot_info(s16 member, s16 target) __asm__("func_800E52A0");

void ai_issue_member_order(AiMemberOrder *order, s16 member, s16 target) __asm__("func_800E3B38");

void ai_issue_member_order(AiMemberOrder *order, s16 member, s16 target)
{
    if (target != 0xFF) {
        get_unit(member);
        order->targetUnit = get_unit(target);
        order->slotInfo = ai_get_member_slot_info(member, target);
        order->value04 = 0;
        order->state = 10;
    } else {
        order->state = 0;
        order->value04 = 0;
    }
}
