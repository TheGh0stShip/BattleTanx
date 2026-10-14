#include "ai_play_stack.h"

void ai_play_stack_push(AiPlayStack *stack, s32 play) __asm__("func_800EA1B8");
void ai_play_stack_pop(AiPlayStack *stack) __asm__("func_800EA1EC");

void ai_play_stack_push(AiPlayStack *stack, s32 play)
{
    ai_play_stack_push_inline(stack, play);
}

void ai_play_stack_pop(AiPlayStack *stack)
{
    stack->depth--;
}
