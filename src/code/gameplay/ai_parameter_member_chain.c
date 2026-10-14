#include "types.h"

typedef struct AiChainRecord {
    u8 pad00[0x2C];
    struct AiChainRecord *next;
} AiChainRecord;

typedef struct AiChainMember {
    u8 pad00[0x18];
    s32 mode;
    u8 pad1C[0x7C];
    AiChainRecord *chain;
} AiChainMember;

typedef struct AiParameterContext {
    u8 pad00[0x8];
    AiChainMember *member;
} AiParameterContext;

f32 ai_member_chain_weight(AiChainMember *member) __asm__("func_800E925C");
f32 ai_parameter_member_chain_weight(AiParameterContext *context) __asm__("func_800E9288");
f32 ai_parameter_inverse_member_chain_weight(AiParameterContext *context) __asm__("func_800E92B8");
f32 ai_parameter_member_mode_is_1(AiParameterContext *context) __asm__("func_800E92F0");

/* 0.2 for every record in the member's linked chain. */
f32 ai_member_chain_weight(AiChainMember *member)
{
    AiChainRecord *record = member->chain;
    f32 weight = 0.0f;

    while (record != 0) {
        record = record->next;
        weight += 0.2f;
    }
    return weight;
}

f32 ai_parameter_member_chain_weight(AiParameterContext *context)
{
    AiChainRecord *record = context->member->chain;
    f32 weight = 0.0f;

    while (record != 0) {
        record = record->next;
        weight += 0.2f;
    }
    return weight;
}

f32 ai_parameter_inverse_member_chain_weight(AiParameterContext *context)
{
    AiChainRecord *record = context->member->chain;
    f32 weight = 0.0f;

    while (record != 0) {
        record = record->next;
        weight += 0.2f;
    }
    return 1.0f - weight;
}

f32 ai_parameter_member_mode_is_1(AiParameterContext *context)
{
    if (context->member->mode == 1) {
        return 1.0f;
    }
    return 0.0f;
}
