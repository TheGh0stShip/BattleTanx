#ifndef AI_PLAY_STACK_H
#define AI_PLAY_STACK_H

#include "types.h"

typedef struct AiActionContext AiActionContext;

/* One record of a play script.  Record 0 of each play is its header:
 * play = the play's own id, state = its initial state, run = entry
 * handler, monitor = called when the play is popped. */
typedef struct AiPlayStep {
    s32 (*run)(AiActionContext *context);
    s32 (*monitor)(AiActionContext *context);
    s32 play;
    s32 state;
} AiPlayStep;

typedef struct AiPlayFrame {
    s32 play;
    s32 state;
} AiPlayFrame;

typedef struct AiPlayStack {
    u32 depth;
    u8 pad04[0x4];
    AiPlayFrame frames[1];
} AiPlayStack;

struct AiActionContext {
    void *team;
    void *owner;
    void *member;
    s32 *memberState;
    AiPlayStack *stack;
    s32 kind;
    u16 memberId;
    u16 ownerId;
    u8 teamIndex;
    u8 pad1D[0x3];
    f32 params[8];
    s32 paramCount;
    s32 unk44;
};

extern AiPlayStep *D_80137888[];

static inline void ai_play_stack_push_inline(AiPlayStack *stack, s32 play)
{
    u32 depth = stack->depth;
    AiPlayStep *steps = D_80137888[play];

    stack->frames[depth].play = play;
    stack->frames[depth].state = steps->state;
    stack->depth = depth + 1;
}

#endif
