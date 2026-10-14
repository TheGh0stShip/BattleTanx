#include "ai_play_stack.h"

typedef struct AiOwnerRecord {
    u8 pad000[0x150];
    AiPlayStack playStack;
    u8 pad160[0x4E];
    u8 teamIndex;
} AiOwnerRecord;

extern u8 D_8033A980[][0x52];

extern AiOwnerRecord *get_entity_record(u16 index) __asm__("func_800A6688");

void ai_init_owner_action_context(AiActionContext *context, s32 ownerId) __asm__("func_800E9940");

void ai_init_owner_action_context(AiActionContext *context, s32 ownerId)
{
    AiOwnerRecord *owner;
    u8 teamIndex;

    context->kind = 1;
    context->memberId = 0xFF;
    context->member = 0;
    context->ownerId = ownerId & 0xFF;
    owner = get_entity_record(ownerId);
    context->owner = owner;
    teamIndex = owner->teamIndex;
    context->memberState = 0;
    context->paramCount = 0;
    context->unk44 = 0;
    context->teamIndex = teamIndex;
    context->team = D_8033A980[teamIndex];
    context->stack = &((AiOwnerRecord *)context->owner)->playStack;
}
