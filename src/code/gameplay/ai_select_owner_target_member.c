#include "types.h"

typedef struct AiActionContext {
    void *team;
    void *owner;
    void *member;
    s32 *memberState;
    void *stack;
    s32 kind;
    u16 memberId;
    u16 ownerId;
    u8 teamIndex;
} AiActionContext;

typedef struct LinkRecord {
    u8 pad00[4];
    u8 active;
    u8 pad05[3];
    f32 distance;
} LinkRecord;

typedef struct SquadTeam {
    u8 pad00[0x30];
    s16 members[15];
    u16 memberCount;
} SquadTeam;

typedef struct SquadOwner {
    u8 pad000[0x1AA];
    u16 targetId;
} SquadOwner;

typedef struct SquadMember {
    u8 pad000[0xB4];
    s32 value0B4;
    u8 pad0B8[0xC4 - 0xB8];
    void *carrier;
    u8 pad0C8[0x359 - 0xC8];
    u8 targetId;
    u8 pad35A[0x4D0 - 0x35A];
    f32 originX;
    f32 originZ;
    f32 directionX;
    f32 directionZ;
    f32 length;
} SquadMember;

typedef struct AiTargetSearchState {
    f32 start[2];
    f32 end[2];
    u8 pad10[4];
    s16 *ids;
    u8 pad18[6];
    u16 count;
    u8 pad20[4];
    void *carrier;
    u8 pad28[8];
} AiTargetSearchState;

extern LinkRecord *get_link_record(s16 fromId, s16 toId) __asm__("func_800E52A0");
extern void *get_entity_by_id(s16 id) __asm__("func_800A03B8");
extern f32 ai_member_horizontal_distance(void *unit, f32 *point) __asm__("func_800E1A20");
extern f32 D_800746C8;
extern f32 D_800746CC;
extern f32 D_800746D0;

s32 ai_select_owner_target_member(AiActionContext *context) __asm__("func_800E6D58");

s32 ai_select_owner_target_member(AiActionContext *context)
{
    AiTargetSearchState state;
    SquadMember *initialMember = context->member;
    SquadMember *member;
    SquadTeam *team = context->team;
    LinkRecord *link;
    register s32 near __asm__("$2");
    register u16 fallback __asm__("$23");
    f32 bestDistance;
    s32 found;
    u16 i;
    register s16 id __asm__("$16");
    register int rawId __asm__("$19");
    void *unit;
    SquadMember *self;
    f32 distance;
    register unsigned best __asm__("$22");

    {
        register s16 targetId __asm__("$19") = initialMember->targetId;
        register s16 *memberIds __asm__("$6") = team->members;

        state.ids = memberIds;
        state.count = team->memberCount;

        if (0xFF != targetId) {
            link = get_link_record(context->memberId, targetId);
            if (link->distance < D_800746C8) {
                ((SquadOwner *)context->owner)->targetId = targetId;
                return -1;
            }
        }
    }

    best = 0xFF;
    bestDistance = D_800746CC;
    member = context->member;
    fallback = 0xFF;
    state.carrier = 0;
    if (member->value0B4 == 1) {
        state.carrier = member->carrier;
    }
    found = 0;
    for (i = 0; i < state.count; i++) {
        id = state.ids[i];
        rawId = state.ids[i];
        link = get_link_record(context->memberId, id);
        if ((link->active != 0) && (link->distance < bestDistance)) {
            unit = get_entity_by_id(id);
            self = context->member;
            state.start[1] = self->originZ;
            state.start[0] = self->originX;
            state.end[1] = state.start[1] + self->directionZ * self->length;
            state.end[0] = state.start[0] + self->directionX * self->length;
            distance = ai_member_horizontal_distance(unit, state.start);
            near = distance + ai_member_horizontal_distance(unit, state.end) <
                   self->length * D_800746D0;
            if (unit == state.carrier) {
                if (near) {
                    fallback = rawId;
                } else {
                    fallback = 0xFF;
                }
            } else if (near) {
                found = 1;
                best = rawId;
                bestDistance = link->distance;
            }
        }
    }

    if (found) {
        ((SquadOwner *)context->owner)->targetId = best;
    } else {
        ((SquadOwner *)context->owner)->targetId = fallback;
    }
    return -1;
}
