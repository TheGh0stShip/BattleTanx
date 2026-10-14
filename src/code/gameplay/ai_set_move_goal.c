#include "types.h"

typedef struct MoveGoal {
    f32 x;
    f32 z;
    u8 pad08[0x8];
    s16 value10;
    u8 pad12[0x2];
    s8 value14;
    s8 value15;
} MoveGoal;

typedef struct MoveUnit {
    u8 pad000[0x24];
    f32 value24;
    u8 pad028[0x4];
    f32 value2C;
    u8 pad030[0x74];
    f32 anchor[2];
    u8 pad0AC[0x288];
    MoveGoal goal;
} MoveUnit;

extern f32 ai_horizontal_length(f32 *offset) __asm__("func_800E0BC4");
extern f32 D_800744F8;

void ai_set_move_goal(MoveUnit *unit, f32 *point) __asm__("func_800E2058");

void ai_set_move_goal(MoveUnit *unit, f32 *point)
{
    MoveGoal *goal = &unit->goal;
    f32 delta[2];
    f32 scale;

    if (point == 0) {
        if (unit->anchor == 0) {
            return;
        }
        delta[1] = unit->anchor[1] - unit->value24;
        delta[0] = unit->anchor[0] - unit->value2C;
        scale = D_800744F8 / ai_horizontal_length(delta);
        goal->z = unit->anchor[1] + delta[1] * scale;
        goal->x = unit->anchor[0] + delta[0] * scale;
    } else {
        goal->z = point[1];
        goal->x = point[0];
    }
    goal->value10 = 0;
    goal->value15 = 1;
    goal->value14 = 1;
}
