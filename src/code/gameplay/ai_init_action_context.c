#include "ai_play_stack.h"

typedef struct AiContextUnit {
    u8 pad000[0x4];
    u8 ownerId;
    u8 pad005[0x97];
    s32 state;
    u8 pad0A0[0x2C];
    AiPlayStack playStack;
} AiContextUnit;

typedef struct AiContextOwner {
    u8 pad000[0x1AE];
    u8 teamIndex;
} AiContextOwner;

extern u8 D_8033A980[][0x52];

extern AiContextUnit *get_unit(s16 id) __asm__("func_800A03B8");
extern AiContextOwner *get_entity_record(u16 index) __asm__("func_800A6688");

void ai_init_action_context(AiActionContext *context, s16 memberId) __asm__("func_800E9894");

void ai_init_action_context(AiActionContext *context, s16 memberId)
{
    AiContextOwner *owner;
    AiContextUnit *member;
    u8 teamIndex;

    context->kind = 2;
    context->memberId = memberId & 0xFF;
    context->member = get_unit(memberId);
    context->ownerId = ((AiContextUnit *)context->member)->ownerId;
    owner = get_entity_record(((AiContextUnit *)context->member)->ownerId);
    context->owner = owner;
    teamIndex = owner->teamIndex;
    member = context->member;
    context->paramCount = 0;
    context->unk44 = 0;
    context->teamIndex = teamIndex;
    context->team = D_8033A980[teamIndex];
    context->memberState = &member->state;
    context->stack = &member->playStack;
}
