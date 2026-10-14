#include "types.h"

typedef struct RouteBuffer {
    u8 data[0x200];
} RouteBuffer;

typedef struct PlanarPoint {
    f32 value0;
    f32 value4;
} PlanarPoint;

typedef struct RouteTarget {
    u8 pad00[8];
    s32 kind;
    u8 pad0C[0x10];
    PlanarPoint position;
    u8 pad24[8];
    s16 count;
} RouteTarget;

typedef struct ScoreMember {
    u8 pad000[0x24];
    f32 value24;
    u8 pad028[4];
    f32 value2C;
    u8 pad030[0x316];
    u16 value346;
    u8 pad348[4];
    RouteTarget *routeTarget;
    u8 pad350[8];
    s8 value358;
} ScoreMember;

typedef struct ScoreTeam {
    u8 pad00[0x30];
    s16 unitIds[15];
    u16 unitCount;
} ScoreTeam;

typedef struct ScoreOwner {
    u8 pad000[0x1A6];
    u8 value1A6;
} ScoreOwner;

typedef struct ScoreUnit {
    u8 pad000;
    u8 active;
    u8 pad002[0x12];
    u16 flags;
    u8 pad016[0x350 - 0x16];
    u8 mode;
} ScoreUnit;

typedef struct LinkRecord {
    u8 pad00[5];
    u8 linked;
    u8 pad06[2];
    f32 distance;
} LinkRecord;

typedef struct ScoreContext {
    ScoreTeam *team;
    ScoreOwner *owner;
    ScoreMember *member;
    u8 pad0C[0xC];
    s16 memberId;
} ScoreContext;

extern void initialize_bitstream_header(RouteBuffer *header) __asm__("func_800DDCA4");
extern void func_800DE1B4(RouteBuffer *header, u16 limit);
extern u16 func_800DE664(RouteBuffer *header, PlanarPoint *from, PlanarPoint *to, s32 a3, s32 a4);
extern ScoreUnit *get_unit(s16 id) __asm__("func_800A03B8");
extern LinkRecord *get_link_record(s16 fromId, s16 toId) __asm__("func_800E52A0");
extern s32 entity_is_targetable(ScoreUnit *unit) __asm__("func_8009FB8C");
extern f32 ai_member_chain_weight(ScoreUnit *unit) __asm__("func_800E925C");
extern void ai_set_indexed_float(ScoreMember *member, s32 key, f32 value) __asm__("func_800E986C");
extern f32 D_80074630;
extern f32 D_80074634;

static inline s32 member_has_route_to_target(ScoreMember *member, RouteTarget *target) {
    RouteBuffer buffer;
    PlanarPoint point;

    if (target == 0) {
        return 0;
    }
    if (target->kind != 0x1B) {
        return 0;
    }
    if (target->count <= 0) {
        return 0;
    }
    point.value4 = member->value24;
    point.value0 = member->value2C;
    initialize_bitstream_header(&buffer);
    func_800DE1B4(&buffer, member->value346 * 3);
    return func_800DE664(&buffer, &point, &target->position, 1, 0) != 0;
}

static inline s32 unit_mode_is_one(ScoreUnit *unit) {
    return unit->mode == 1;
}

s16 ai_select_best_scored_unit(ScoreContext *context, f32 *weights, s32 *keepTarget) __asm__("func_800E3CF0");

s16 ai_select_best_scored_unit(ScoreContext *context, f32 *weights, s32 *keepTarget) {
    ScoreOwner *owner = context->owner;
    ScoreTeam *team;
    s16 *ids;
    ScoreUnit *unit;
    LinkRecord *link;
    s16 bestId;
    s16 id;
    u16 count;
    u16 i;
    f32 bestScore;
    f32 score;
    s32 isFlagged;

    if (keepTarget != 0) {
        ScoreMember *member = context->member;
        if (member_has_route_to_target(member, member->routeTarget)) {
            *keepTarget = 1;
            return 0xFF;
        }
        *keepTarget = 0;
        context->member->routeTarget = 0;
        context->member->value358 = 0;
    }
    bestId = 0xFF;
    bestScore = weights[0] - D_80074630;
    team = context->team;
    count = team->unitCount;
    ids = team->unitIds;
    for (i = 0; i < count; i++) {
        id = ids[i];
        unit = get_unit(id);
        if (unit->active != 0) {
            link = get_link_record(context->memberId, id);
            score = 0.0f;
            if (link->linked != 0 && entity_is_targetable(unit) != 0) {
                score = weights[1] + score;
            }
            score += weights[2] * ai_member_chain_weight(unit);
            if (unit_mode_is_one(unit)) {
                score += weights[4];
            }
            isFlagged = unit->flags & 4;
            if (isFlagged) {
                score += weights[3];
            }
            score += weights[5] * link->distance * D_80074634;
            if (isFlagged && owner->value1A6 == 0) {
                score = 0.0f;
            }
            if (bestScore < score) {
                bestId = id;
                bestScore = score;
            }
        }
    }
    if (bestId == 0xFF && keepTarget != 0 && *keepTarget == 0) {
        ai_set_indexed_float(context->member, 0x1002, 0.0f);
    }
    return bestId;
}
