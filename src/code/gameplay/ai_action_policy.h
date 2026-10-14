#ifndef AI_ACTION_POLICY_H
#define AI_ACTION_POLICY_H

#include "types.h"

typedef struct AiActionContext AiActionContext;
typedef struct AiActionPolicy AiActionPolicy;

extern s32 ai_select_weighted_action(AiActionContext *context, AiActionPolicy *policy)
    __asm__("func_800EA93C");

#endif
