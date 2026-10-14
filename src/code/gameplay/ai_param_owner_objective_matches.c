#include "ai_play_stack.h"

typedef struct ObjectiveOwner {
    u8 pad000[0x1A8];
    u16 objective;
} ObjectiveOwner;

/* Weight returned when the owner's objective matches. */
extern f32 D_80074778;

f32 ai_param_owner_objective_matches(AiActionContext *context, u16 objective) __asm__("func_800E837C");

f32 ai_param_owner_objective_matches(AiActionContext *context, u16 objective)
{
    f32 weight;

    weight = D_80074778;
    if (((ObjectiveOwner *)context->owner)->objective != objective) {
        weight = 0.0f;
    }
    return weight;
}
