#include "types.h"

typedef struct ActionContext {
    u8 pad00[0xC];
    void *owner;
    u8 pad10[8];
    s16 action;
    u16 parameter;
} ActionContext;

extern void func_800E3980(void *owner, s16 action, u16 parameter, s32 enabled);

s32 dispatch_context_action(ActionContext *context) __asm__("func_800E69A4");

s32 dispatch_context_action(ActionContext *context)
{
    func_800E3980(context->owner, context->action, context->parameter, 1);
    return -1;
}
