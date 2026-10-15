#include "ai_play_stack.h"

typedef struct AiPlayOwner {
    u8 pad000[0x18];
    void *activeObject;
    u8 pad01C[0x150 - 0x01C];
    AiPlayStack playStack;
    u8 pad160[0x1AE - 0x160];
    u8 teamIndex;
} AiPlayOwner;

extern AiPlayOwner *get_entity_record(u16 id) __asm__("func_800A6688");
extern void ai_play_stack_update(AiActionContext *context) __asm__("func_800EA478");
extern u8 D_8033A980[][0x52];

void ai_update_owner_play_stack(u16 ownerId) __asm__("func_800EA89C");

void ai_update_owner_play_stack(u16 ownerId)
{
    AiActionContext context;
    AiPlayOwner *owner;

    owner = get_entity_record(ownerId);
    context.owner = owner;
    if (owner->activeObject != 0) {
        context.kind = 1;
        context.ownerId = ownerId;
        context.teamIndex = owner->teamIndex;
        context.stack = &owner->playStack;
        context.memberId = 0xFF;
        context.member = 0;
        context.memberState = 0;
        context.paramCount = 0;
        context.unk44 = 0;
        context.team = D_8033A980[owner->teamIndex];
        ai_play_stack_update(&context);
    }
}
