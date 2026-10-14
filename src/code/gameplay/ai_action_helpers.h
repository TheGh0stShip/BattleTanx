#ifndef AI_ACTION_HELPERS_H
#define AI_ACTION_HELPERS_H

#include "types.h"

typedef struct AiActionContext {
    u8 pad00[0x4];
    void *controller;
    void *owner;
    void *member;
    u8 pad10[0x8];
    s16 linkIndex;
    u16 targetId;
} AiActionContext;

#endif
