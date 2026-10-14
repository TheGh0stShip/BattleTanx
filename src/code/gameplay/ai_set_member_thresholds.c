#include "ai_play_stack.h"

typedef struct AiThresholdMember {
    u8 pad000[0x1C];
    s32 value;
    u8 pad020[0x33C];
    s16 threshold;
} AiThresholdMember;

s32 ai_set_member_threshold_minus_one(AiActionContext *context) __asm__("func_800E7458");
s32 ai_set_member_threshold_half(AiActionContext *context) __asm__("func_800E7470");

s32 ai_set_member_threshold_minus_one(AiActionContext *context)
{
    AiThresholdMember *member = context->member;
    member->threshold = member->value - 1;
    return -1;
}

s32 ai_set_member_threshold_half(AiActionContext *context)
{
    AiThresholdMember *member = context->member;
    member->threshold = member->value / 2;
    return -1;
}
