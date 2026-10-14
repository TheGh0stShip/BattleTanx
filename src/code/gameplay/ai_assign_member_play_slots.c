#include "ai_play_stack.h"

typedef struct AiSquadUnit {
    u8 pad000[0x1];
    u8 inUse;
    u8 pad002[0x2];
    u8 ownerId;
    u8 pad005[0x97];
    s32 state;
    u8 pad0A0[0x2C];
    AiPlayStack playStack;
    u8 pad0DC[0x27B];
    u8 unitClass;
} AiSquadUnit;

typedef struct AiSquadOwner {
    s16 memberIds[5];
    u8 pad00A[0xE];
    s32 active;
    u8 pad01C[0x130];
    s32 playTable;
    u8 pad150[0x5E];
    u8 teamIndex;
} AiSquadOwner;

/* Context passed to the play-slot scorers (see ai_play_scorers.c). */
typedef struct AiScoreContext {
    u16 memberId;
    u16 ownerId;
    AiSquadUnit *member;
    AiSquadOwner *owner;
    void *team;
    s32 memberPlay;
    s32 slotPlay;
} AiScoreContext;

typedef struct AiPlaySlot {
    s32 play;
    f32 (*score)(AiScoreContext *context);
} AiPlaySlot;

typedef struct AiSquadCandidate {
    u16 id;
    AiSquadUnit *member;
    s32 play;
} AiSquadCandidate;

extern AiPlaySlot *D_80135CF8[];
extern u8 D_8033A980[][0x52];

extern AiSquadUnit *get_unit(s16 id) __asm__("func_800A03B8");
extern void *get_entity(u16 id) __asm__("func_800A6688");
extern void ai_play_stack_push(AiPlayStack *stack, s32 play) __asm__("func_800EA1B8");
extern void ai_play_stack_unwind(AiActionContext *context, u32 depth) __asm__("func_800EA1FC");

void ai_assign_member_play_slots(AiActionContext *context) __asm__("func_800E9E5C");

void ai_assign_member_play_slots(AiActionContext *context)
{
    AiScoreContext score;
    AiSquadCandidate candidates[5];
    AiActionContext action;
    AiActionContext *actionContext;
    AiSquadCandidate *candidate;
    AiSquadCandidate *chosen;
    AiPlaySlot *slot;
    f32 best;
    f32 value;
    u16 remaining;
    u16 n;
    u16 i;

    score.owner = context->owner;
    remaining = 0;
    if (score.owner->active == 0) {
        return;
    }
    score.ownerId = context->ownerId;
    score.team = D_8033A980[score.owner->teamIndex];
    for (n = 0; n < 5; n++) {
        s16 id = score.owner->memberIds[n];
        AiSquadUnit *unit = get_unit(id);

        if (unit->inUse != 0 && unit->unitClass != 0x42 && unit->state != 8) {
            candidates[n].id = id;
            candidates[n].member = unit;
            if (unit->playStack.depth == 0) {
                candidates[n].play = 0;
            } else {
                candidates[n].play = unit->playStack.frames[0].play;
            }
            remaining++;
        } else {
            candidates[n].id = 0xFF;
            candidates[n].member = 0;
            candidates[n].play = 0;
        }
    }
    slot = D_80135CF8[score.owner->playTable];
    score.slotPlay = slot->play;
    if (remaining == 0) {
        return;
    }
    do {
        best = 0.0f;
        chosen = 0;
        for (i = 0; i < 5; i++) {
            candidate = &candidates[i];
            if (candidate->member == 0) {
                continue;
            }
            score.memberId = candidate->id;
            score.member = candidate->member;
            score.memberPlay = score.member->playStack.depth ? score.member->playStack.frames[0].play : 0;
            if (slot->score == 0) {
                chosen = candidate;
                break;
            }
            if (score.member->unitClass == 0x42) {
                continue;
            }
            value = slot->score(&score);
            if (best < value) {
                best = value;
                chosen = candidate;
                if (1.0f <= best) {
                    break;
                }
            }
        }
        if (chosen != 0) {
            if (chosen->play != slot->play) {
                u16 id = chosen->id;

                actionContext = &action;
                action.kind = 2;
                action.memberId = (u8)id;
                action.member = get_unit(id);
                action.ownerId = ((AiSquadUnit *)action.member)->ownerId;
                action.owner = get_entity(((AiSquadUnit *)action.member)->ownerId);
                action.teamIndex = ((AiSquadOwner *)action.owner)->teamIndex;
                action.team = D_8033A980[action.teamIndex];
                action.memberState = &((AiSquadUnit *)action.member)->state;
                action.stack = &((AiSquadUnit *)action.member)->playStack;
                action.paramCount = 0;
                action.unk44 = 0;
                ai_play_stack_unwind(actionContext, 0);
                ai_play_stack_push(action.stack, slot->play);
            }
            remaining--;
            chosen->id = 0xFF;
            chosen->member = 0;
        }
        if (slot[1].play != 0) {
            slot++;
            score.slotPlay = slot->play;
        }
    } while (remaining != 0);
}
