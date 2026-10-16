#include "types.h"

typedef struct AiActionContext AiActionContext;

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

typedef struct AiPlayStackSlots {
    AiPlayFrame slots[1];
} AiPlayStackSlots;

struct AiActionContext {
    void *team;
    void *owner;
    void *member;
    s32 *memberState;
    AiPlayStack *stack;
};

extern AiPlayStep *D_80137888[];
extern s32 ai_select_root_play(AiActionContext *context) __asm__("func_800EA2A4");

static inline void ai_play_stack_push_inline(AiPlayStack *stack, s32 play)
{
    u32 depth = stack->depth;
    AiPlayStep *steps = D_80137888[play];

    stack->frames[depth].play = play;
    stack->frames[depth].state = steps->state;
    stack->depth = depth + 1;
}

static inline void ai_play_stack_unwind(AiActionContext *context, u32 depth)
{
    AiPlayStep *steps;

    while (depth < context->stack->depth) {
        steps = D_80137888[((AiPlayStackSlots *)context->stack)->slots[context->stack->depth].play];
        if (steps->monitor) {
            steps->monitor(context);
        }
        context->stack->depth--;
    }
}

static inline void ai_play_stack_push_root(AiActionContext *context)
{
    AiPlayStep *steps = D_80137888[ai_select_root_play(context)];
    s32 state;

    ai_play_stack_push_inline(context->stack, steps->play);
    if (steps->run) {
        state = steps->run(context);
        if (state != -1) {
            context->stack->frames[context->stack->depth].state = state;
        }
    }
}

static inline s32 ai_play_stack_top(AiPlayStack *stack)
{
    u16 depth = stack->depth;

    if (depth == 0) {
        return 0;
    }
    return stack->frames[depth - 1].play;
}

void ai_play_stack_update(AiActionContext *context) __asm__("func_800EA478");

void ai_play_stack_update(AiActionContext *context)
{
    u16 count;
    u16 i;
    AiPlayFrame *frame;
    AiPlayStep *steps;
    s32 state;
    s32 next;
    s32 play;
    u16 depth;
    s32 top;
    s32 r2;
    s32 prev;
    s32 nstate;
    s32 (*fn)(AiActionContext *context);

    depth = context->stack->depth;
    if (depth == 0) {
        top = 0;
    } else {
        goto compute;
    store_step:
        frame->state = r2;
        return;
    store_run:
        frame->state = nstate;
        return;
    compute:
        top = context->stack->frames[depth - 1].play;
    }
    if (top == 0) {
        ai_play_stack_push_root(context);
    }
    count = context->stack->depth - 1;
    for (i = 0; i < count; i++) {
        frame = &context->stack->frames[i];
        state = frame->state;
        prev = frame->play;
        steps = D_80137888[prev];
        fn = steps[state].monitor;
        if (fn == 0) {
            continue;
        }
        next = fn(context);
        if ((next == -1) | (next == state)) {
            continue;
        }
        ai_play_stack_unwind(context, i + 1);
        frame->state = next;
        break;
    }
    do {
    frame = &context->stack->frames[i];
    state = frame->state;
    steps = D_80137888[frame->play];
    if (state == -2) {
        fn = steps->monitor;
        if (fn) {
            fn(context);
        }
        context->stack->depth--;
        i--;
        frame = &context->stack->frames[i];
        prev = frame->play;
        do {
            steps = D_80137888[prev];
            state = steps[frame->state].state;
            if (state != -1) {
                frame->state = state;
            }
            return;
        } while (0);
    }
        fn = steps[state].run;
        if (fn == 0) {
            nstate = steps[state].state;
            do {
                if (nstate == -1) {
                    nstate = state;
                }
            } while (0);
        } else {
            r2 = fn(context);
            if (r2 == -1) {
                nstate = steps[state].state;
                if (nstate == -1) {
                    nstate = state;
                }
            } else if (r2 != state) {
                goto store_step;
            } else {
                nstate = state;
            }
        }
        play = steps[state].play;
        if (play == 0) {
            goto store_run;
        }
    } while (0);
        do {
            AiPlayStep *pushed = D_80137888[play];
            s32 r;

            ai_play_stack_push_inline(context->stack, play);
            fn = pushed->run;
            if (fn) {
                r = fn(context);
                if (r != -1) {
                    context->stack->frames[context->stack->depth].state = r;
                }
            }
        } while (0);
}
