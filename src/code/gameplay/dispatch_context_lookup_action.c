#include "types.h"

typedef struct ActionContext {
    u8 pad00[0xC];
    void *owner;
    u8 pad10[8];
    s16 action;
} ActionContext;

extern s32 D_80135860;

extern s16 func_800E3CF0(ActionContext *context, s32 *table, s32 index);
extern void func_800E3AB0(void *owner, s16 action, s16 value);

s32 dispatch_context_lookup_action(ActionContext *context) __asm__("func_800E69D4");

s32 dispatch_context_lookup_action(ActionContext *context)
{
    s16 value = func_800E3CF0(context, &D_80135860, 0);

    if (value != 0xFF) {
        func_800E3AB0(context->owner, context->action, value);
    }
    return -1;
}
