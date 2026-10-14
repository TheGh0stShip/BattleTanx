#include "ai_play_stack.h"

/* The unwind loop addresses the stack as 1-based slots overlaying the
 * header: slots[depth] is the top frame (frames[depth - 1]). */
typedef struct AiPlayStackSlots {
    AiPlayFrame slots[1];
} AiPlayStackSlots;

typedef struct AiPlayOwner {
    u8 pad000[0x1A6];
    u8 rootPlayFlag;
} AiPlayOwner;

typedef struct AiPlayMember {
    u8 pad000[0x14];
    u16 flags;
    u8 pad016[0x341];
    u8 unitClass;
} AiPlayMember;

extern s32 *get_game_mode(void) __asm__("func_8007AAF4");
extern s32 ai_member_status_is_1(AiPlayMember *member) __asm__("func_800E3470");

void ai_play_stack_unwind(AiActionContext *context, u32 depth) __asm__("func_800EA1FC");
s32 ai_select_root_play(AiActionContext *context) __asm__("func_800EA2A4");
void ai_play_stack_push_root(AiActionContext *context) __asm__("func_800EA3D0");

inline void ai_play_stack_unwind(AiActionContext *context, u32 depth)
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

s32 ai_select_root_play(AiActionContext *context)
{
    s32 *mode = get_game_mode();

    switch (context->kind) {
    case 1:
        if (((AiPlayOwner *)context->owner)->rootPlayFlag) {
            switch (*mode) {
            case 0:
            case 1:
            case 3:
            case 6:
                return 0xF;
            case 2:
                return 0x19;
            case 4:
            case 5:
            case 7:
            case 9:
                return 2;
            }
            return 0xC;
        }
        return *mode == 2 ? 0x1A : 0xA;
    case 2:
        switch (((AiPlayMember *)context->member)->unitClass) {
        case 0x42:
        case 0x46:
            return 3;
        case 0x41:
        case 0x43:
        case 0x45:
            return 5;
        }
        if (((AiPlayMember *)context->member)->flags & 4) {
            return 1;
        }
        if (ai_member_status_is_1(context->member)) {
            return 0xB;
        }
        return 5;
    }
    return 0xC;
}

inline void ai_play_stack_push_root(AiActionContext *context)
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
