#include "ai_play_stack.h"

typedef struct AiPlayMember {
    u8 pad000[0x4];
    u8 ownerId;
    u8 pad005[0x97];
    s32 state;
    u8 pad0A0[0x2C];
    AiPlayStack playStack;
} AiPlayMember;

extern void *get_entity(u16 id) __asm__("func_800A6688");
extern void ai_play_stack_update(AiActionContext *context) __asm__("func_800EA478");

void ai_update_member_plays(void *team, AiPlayMember *member, u8 teamIndex, u8 memberId) __asm__("func_800EA828");

/* Run one update of a squad member's play stack. */
void ai_update_member_plays(void *team, AiPlayMember *member, u8 teamIndex, u8 memberId)
{
    AiActionContext context;
    u8 ownerId;

    context.kind = 2;
    context.memberId = memberId;
    ownerId = member->ownerId;
    context.teamIndex = teamIndex;
    context.team = team;
    context.ownerId = ownerId;
    context.owner = get_entity(ownerId);
    context.member = member;
    context.memberState = &member->state;
    context.stack = &member->playStack;
    context.paramCount = 0;
    context.unk44 = 0;
    ai_play_stack_update(&context);
}
