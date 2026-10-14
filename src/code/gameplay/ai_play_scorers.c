#include "types.h"

typedef struct AiSquadMember {
    u8 pad00[0x14];
    u16 flags;
    u8 pad16[0x2];
    u32 mode;
    u8 pad1C[0x8];
    f32 x;
    f32 y;
    f32 z;
    u8 pad30[0x6C];
    s32 state;
} AiSquadMember;

typedef struct AiSquadOwner {
    u8 pad000[0x1A8];
    u16 objectiveId;
} AiSquadOwner;

typedef struct AiScoreContext {
    u16 memberId;
    u8 pad02[0x2];
    AiSquadMember *member;
    AiSquadOwner *owner;
    u8 pad0C[0x4];
    s32 memberPlay;
    s32 slotPlay;
} AiScoreContext;

extern f32 ai_horizontal_length(f32 *offset) __asm__("func_800E0BC4");
extern f32 ai_member_horizontal_distance(AiSquadMember *member, f32 *point) __asm__("func_800E1A20");
extern s32 ai_member_status_is_2(AiSquadMember *member) __asm__("func_800E3460");
extern s32 ai_member_status_is_1(AiSquadMember *member) __asm__("func_800E3470");
extern s32 ai_find_object_position(u16 id, f32 *point, s32 arg2) __asm__("func_800E377C");

f32 ai_score_member_mode(AiScoreContext *context) __asm__("func_800E9A9C");
f32 ai_score_member_mode_flag_favored(AiScoreContext *context) __asm__("func_800E9B24");
f32 ai_score_member_mode_duplicate(AiScoreContext *context) __asm__("func_800E9B9C");
f32 ai_score_member_objective_distance(AiScoreContext *context) __asm__("func_800E9C24");
f32 ai_score_member_on_play_status_2(AiScoreContext *context) __asm__("func_800E9D30");
f32 ai_score_member_on_slot_play(AiScoreContext *context) __asm__("func_800E9D80");
f32 ai_score_member_origin_proximity(AiScoreContext *context) __asm__("func_800E9DA4");

f32 ai_score_member_mode(AiScoreContext *context)
{
    AiSquadMember *member;
    f32 score;

    if (context->memberPlay == context->slotPlay) {
        return 1.0f;
    }
    member = context->member;
    switch (member->mode) {
    case 2:
        score = 0.8f;
        if (member->flags & 4) {
            score = 0.1f;
        }
        return score;
    case 0:
        return 0.9f;
    case 1:
    default:
        return 0.5f;
    }
}

f32 ai_score_member_mode_flag_favored(AiScoreContext *context)
{
    AiSquadMember *member;
    f32 score;

    if (context->memberPlay == context->slotPlay) {
        return 1.0f;
    }
    member = context->member;
    switch (member->mode) {
    case 2:
        score = 0.9f;
        if (member->flags & 4) {
            score = 1.0f;
        }
        return score;
    case 0:
        return 0.7f;
    case 1:
    default:
        return 0.1f;
    }
}

f32 ai_score_member_mode_duplicate(AiScoreContext *context)
{
    AiSquadMember *member;
    f32 score;

    if (context->memberPlay == context->slotPlay) {
        return 1.0f;
    }
    member = context->member;
    switch (member->mode) {
    case 2:
        score = 0.8f;
        if (member->flags & 4) {
            score = 0.1f;
        }
        return score;
    case 0:
        return 0.9f;
    case 1:
    default:
        return 0.5f;
    }
}

f32 ai_score_member_objective_distance(AiScoreContext *context)
{
    AiSquadMember *member;
    f32 point[2];
    f32 distance;
    f32 score;

    if (context->memberPlay == context->slotPlay) {
        return 1.0f;
    }
    if (ai_find_object_position(context->owner->objectiveId, point, 1)) {
        distance = ai_member_horizontal_distance(context->member, point);
        if (distance < 1000.0f) {
            return distance / 2000.0f + 0.5f;
        }
        member = context->member;
        switch (member->mode) {
        case 2:
            score = 0.2f;
            if (member->flags & 4) {
                score = 0.1f;
            }
            return score;
        case 0:
            return 0.3f;
        case 1:
            return 0.4f;
        }
    }
    return 0.0f;
}

f32 ai_score_member_on_play_status_2(AiScoreContext *context)
{
    if (context->memberPlay == context->slotPlay && ai_member_status_is_2(context->member)) {
        return 1.0f;
    }
    return 0.0f;
}

f32 ai_score_member_on_slot_play(AiScoreContext *context)
{
    if (context->memberPlay == context->slotPlay) {
        return 1.0f;
    }
    return 0.0f;
}

f32 ai_score_member_origin_proximity(AiScoreContext *context)
{
    f32 offset[2];
    f32 score;
    f32 proximity;
    s32 state;

    if (ai_member_status_is_1(context->member)) {
        return 0.0f;
    }
    state = context->member->state;
    offset[1] = context->member->x;
    offset[0] = context->member->z;
    score = 0.0f;
    if (state == 8 || state == 9) {
        score = 0.5f;
    }
    proximity = 0.5f - ai_horizontal_length(offset) / 16000.0f;
    if (0.0f < proximity) {
        score += proximity;
    }
    return score;
}
