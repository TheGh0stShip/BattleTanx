#include "types.h"

typedef struct AiMemberState {
    s32 value0;
    s32 value1;
    u8 pad08[0x33C];
    s16 order;
    u8 pad346[2];
    u8 state348;
    u8 state349;
    u8 state34A;
} AiMemberState;

void ai_clear_member_values(AiMemberState *member) __asm__("func_800E3480");
void ai_clear_member_order_state(AiMemberState *member) __asm__("func_800E348C");

void ai_clear_member_values(AiMemberState *member)
{
    member->value0 = 0;
    member->value1 = 0;
}

void ai_clear_member_order_state(AiMemberState *member)
{
    member->order = 0;
    member->state34A = 0;
    member->state348 = 0;
}
