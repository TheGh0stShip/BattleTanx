#include "types.h"

typedef struct UnitLink {
    u8 pad00[0x4];
    u8 active;
    u8 pad05[0x3];
    f32 distance;
} UnitLink;

typedef struct LinkTeam {
    u8 pad00[0x8];
    s16 members[15];
    u16 memberCount;
    u8 pad28[0x2A];
} LinkTeam;

typedef struct LinkUnit {
    u8 pad000[0x4];
    u8 ownerId;
    u8 pad005[0x354];
    u8 nearestMember;
} LinkUnit;

typedef struct LinkOwner {
    u8 pad000[0x1AE];
    u8 teamIndex;
} LinkOwner;

extern u8 D_8033B450[][20];
extern UnitLink D_8033AAE8[];
extern LinkTeam D_8033A980[];

extern LinkUnit *get_unit(s16 id) __asm__("func_800A03B8");
extern LinkOwner *get_entity_record(u16 index) __asm__("func_800A6688");

void select_nearest_linked_member(s16 id) __asm__("func_800E5DE4");

static inline UnitLink *get_unit_link(s16 fromId, s16 toId) {
    if (fromId < toId) {
        return &D_8033AAE8[D_8033B450[fromId][toId]];
    }
    if (toId < fromId) {
        return &D_8033AAE8[D_8033B450[toId][fromId]];
    }
    return 0;
}

void select_nearest_linked_member(s16 id) {
    LinkUnit *unit;
    LinkTeam *team;
    UnitLink *link;
    f32 best;
    s16 nearest;
    s16 other;
    u16 i;
    s16 *members;

    unit = get_unit(id);
    team = &D_8033A980[get_entity_record(unit->ownerId)->teamIndex];
    nearest = 0xFF;
    best = 16000.0f;
    members = team->members;
    for (i = 0; i < team->memberCount; i++) {
        other = members[i];
        if (id != other) {
            link = get_unit_link(id, other);
            if (link->active && link->distance < best) {
                best = link->distance;
                nearest = other;
            }
        }
    }
    unit->nearestMember = nearest;
}


typedef struct AiUnit {
    u8 pad000;
    u8 alive;
    u8 pad002[0x22];
    f32 x;
    u8 pad028[4];
    f32 z;
    u8 pad030[0x104];
    u8 nav[8];
    u16 navState;
    u8 pad13E[0x1FE];
    f32 navDistance;
    u8 pad340[0xC];
    s32 value34C;
    u8 pad350[0xB];
    u8 navResult;
} AiUnit;

typedef struct AiLinkInfo {
    u8 first;
    u8 second;
    u8 pad02[3];
    u8 active;
} AiLinkInfo;

typedef struct AiTarget {
    u8 pad00[4];
    void *link;
} AiTarget;

typedef struct AiGoal {
    u32 mode;
    f32 *point;
    f32 pos[2];
    void *target;
    void *aux;
} AiGoal;

extern f32 get_ai_distance_scale(void) __asm__("func_800E1ED0");
extern f32 ai_horizontal_distance(f32 *a, f32 *b) __asm__("func_800E0C8C");
extern s32 entity_is_targetable(void *unit) __asm__("func_8009FB8C");
extern u8 func_800DFA68(void *nav, f32 *from, f32 *to, AiUnit *unit);
extern u16 extend_route_three_steps() __asm__("func_800E031C");
extern void ai_set_move_goal(AiUnit *unit, f32 *point) __asm__("func_800E2058");
extern void update_action_goal(AiGoal *goal) __asm__("func_800E360C");
extern void clear_member_transient_state(AiGoal *goal) __asm__("func_800E3480");
extern void func_800E349C(AiUnit *unit);
extern s32 check_unit_route_to_kind1b_target(AiUnit *unit, void *object, void *owner) __asm__("func_800E3C34");
extern AiUnit *get_ai_unit(s16 id) __asm__("func_800A03B8");
extern u8 D_8033B44A;

static inline void ai_goal_follow_action(AiUnit *u, AiGoal *g, f32 *pos, s32 canRoute, s32 *budget)
{
    void *n = u->nav;
    f32 *t = g->pos;

    update_action_goal(g);
    if (canRoute != 0) {
        u->navResult = func_800DFA68(n, pos, t, u);
        *budget = 0;
    }
}

void ai_update_goal(AiUnit *unit, AiGoal *goal, f32 *pos, s32 *budget, f32 *outNear, f32 *outFar)
    __asm__("func_800E5FA8");



typedef struct AiOwnerState {
    u8 pad00[0x24];
    f32 value24;
    u8 pad28[0x4];
    f32 value2C;
    u8 pad30[0x9C - 0x30];
    s32 value9C;
} AiOwnerState;

extern f32 *ai_get_indexed_float_address(AiOwnerState *store, s32 index) __asm__("func_800E9880");

void reset_owner_state(AiOwnerState *owner) __asm__("func_800E5F30");

void reset_owner_state(AiOwnerState *owner) {
    f32 point[2];
    s32 flag;

    point[1] = owner->value24;
    flag = 1;
    point[0] = owner->value2C;
    ai_update_goal((AiUnit *)owner, (AiGoal *)&owner->value9C, point, &flag, ai_get_indexed_float_address(owner, 0x1004),
                  ai_get_indexed_float_address(owner, 0x1005));
}

void ai_update_goal(AiUnit *unit, AiGoal *goal, f32 *pos, s32 *budget, f32 *outNear, f32 *outFar)
{
    f32 scale;
    f32 dist;
    s32 canRoute;
    AiLinkInfo *link;
    void *nav;
    f32 *to;
    f32 tmp[2];
    f32 tmp2[2];

    scale = get_ai_distance_scale() * 0.5f;
    dist = 16000.0f;
    canRoute = 0;
    if (budget != 0) {
        canRoute = *budget;
    }
    switch (goal->mode) {
    case 0:
        break;
    case 4:
        if (goal->target == 0 || goal->aux != ((AiTarget *)goal->target)->link) {
            { clear_member_transient_state(goal); break; }
        }
        goal->point = goal->pos;
        dist = ai_horizontal_distance(pos, goal->point);
        break;
    case 1: {
        AiUnit *t1;
        t1 = goal->target;
        link = goal->aux;
        if (t1->alive == 0 || link->active == 0 || !entity_is_targetable(t1)) {
            { clear_member_transient_state(goal); break; }
        }
        goal->point[1] = t1->x;
        goal->point[0] = t1->z;
        dist = ai_horizontal_distance(pos, goal->point);
        break;
    }
    case 5: {
        AiUnit *t5 = goal->target;
        void *nav5 = unit->nav;
        if (t5->alive == 0) {
            { clear_member_transient_state(goal); break; }
        }
        if (canRoute != 0) {
            tmp[1] = t5->x;
            tmp[0] = t5->z;
            unit->navResult = func_800DFA68(nav5, pos, tmp, unit);
            *budget = 0;
        }
        dist = unit->navDistance;
        break;
    }
    case 3:
        if (!check_unit_route_to_kind1b_target(unit, goal->target, goal->aux)) {
            clear_member_transient_state(goal);
            unit->value34C = 0;
        }
        break;
    case 9:
        if (unit->navDistance < 40.0f) {
            func_800E349C(unit);
            break;
        }
        ai_set_move_goal(unit, goal->pos);
        dist = unit->navDistance;
        break;
    case 8: {
        ai_goal_follow_action(unit, goal, pos, canRoute, budget);
        dist = unit->navDistance;
        break;
    }
    case 6:
    case 12: {
        f32 d;
        tmp[1] = unit->x;
        tmp[0] = unit->z;
        to = goal->pos;
        nav = unit->nav;
        d = ai_horizontal_distance(tmp, to);
        if (d < 500.0f && (d < 300.0f || unit->navState == 1)) {
            ai_set_move_goal(unit, 0);
        } else if (canRoute != 0) {
            unit->navResult = func_800DFA68(nav, pos, to, unit);
            *budget = 0;
        }
        dist = unit->navDistance;
        break;
    }
    case 7: {
        void *nav7 = unit->nav;
        f32 *to7 = goal->pos;
        if (canRoute != 0) {
            unit->navResult = func_800DFA68(nav7, pos, to7, unit);
            *budget = 0;
        }
        dist = unit->navDistance;
        break;
    }
    case 10: {
        AiUnit *t10;
        void *nav10;
        t10 = goal->target;
        nav10 = unit->nav;
        if (t10->alive == 0) {
            clear_member_transient_state(goal);
            break;
        }
        if (t10 == get_ai_unit(D_8033B44A ? ((AiLinkInfo *)goal->aux)->first
                                          : ((AiLinkInfo *)goal->aux)->second)) {
            goal->point = 0;
            break;
        }
        if (canRoute != 0) {
            tmp2[1] = t10->x;
            tmp2[0] = t10->z;
            extend_route_three_steps(nav10, pos, tmp2);
            *budget = 0;
        }
        dist = unit->navDistance;
        break;
    }
    }
    if (dist <= scale) {
        *outNear = 1.0f;
    } else {
        *outNear = scale / dist;
    }
    *outFar = dist / 16000.0f;
}
