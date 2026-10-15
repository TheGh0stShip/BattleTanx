#include "types.h"

typedef struct ActionTargetEntity {
    u8 pad00;
    u8 alive;
    u8 pad02[0x22];
    f32 x;
    u8 pad28[0x4];
    f32 z;
} ActionTargetEntity;

typedef struct UnitAction {
    u32 state;
    s32 value04;
    f32 z;
    f32 x;
    ActionTargetEntity *target;
} UnitAction;

typedef struct ActionUnit {
    u8 pad000;
    u8 alive;
    u8 pad002[0x22];
    f32 x;
    u8 pad028[0x4];
    f32 z;
    u8 pad030[0x6C];
    UnitAction action;
    u8 pad0B0[0x294];
    u16 value344;
    u8 pad346[0x2];
    u8 value348;
    u8 pad349;
    u8 value34A;
} ActionUnit;

typedef struct ActionGoal {
    s32 kind;
    f32 *point;
    f32 z;
    f32 x;
    u8 unitId;
    u8 pad11[0x3];
    ActionUnit *unit;
} ActionGoal;

extern ActionUnit *get_unit(s16 id) __asm__("func_800A03B8");

void update_action_goal(ActionGoal *goal) __asm__("func_800E360C");

void update_action_goal(ActionGoal *goal)
{
    ActionUnit *cached = goal->unit;
    ActionUnit *unit = get_unit(goal->unitId);
    UnitAction *action;
    ActionTargetEntity *target;
    f32 x;
    f32 z;

    if (cached->alive == 0) {
        goal->kind = 0;
        goal->point = 0;
        return;
    }
    action = &cached->action;
    if (cached->value344 == 0) {
        x = unit->x;
        z = unit->z;
        goal->point = &goal->z;
        goal->kind = 9;
        goal->x = x;
        goal->z = z;
    }
    switch (action->state) {
    case 5:
        target = action->target;
        if (target->alive != 0) {
            goal->x = target->x;
            goal->z = target->z;
            return;
        }
        break;
    case 6:
    case 7:
    case 8:
        goal->x = action->x;
        goal->z = action->z;
        return;
    case 0:
    case 9:
        break;
    }
    unit->action.state = 0;
    unit->action.value04 = 0;
    unit->value344 = 0;
    unit->value34A = 0;
    unit->value348 = 0;
}
