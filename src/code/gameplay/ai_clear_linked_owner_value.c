#include "ai_action_helpers.h"

typedef struct AiLinkedObject {
    u8 pad00[0x18];
    s32 value;
} AiLinkedObject;

typedef struct AiOwnerLink {
    u8 pad000[0x4FC];
    AiLinkedObject *linked;
} AiOwnerLink;

s32 ai_clear_linked_owner_value(AiActionContext *context) __asm__("func_800E73A4");

s32 ai_clear_linked_owner_value(AiActionContext *context)
{
    AiLinkedObject *linked = ((AiOwnerLink *)context->owner)->linked;
    if (linked != 0) {
        linked->value = 0;
    }
    return -1;
}
