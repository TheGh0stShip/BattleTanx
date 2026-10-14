#include "ai_action_helpers.h"

typedef struct AiOwnerWord360 {
    u8 pad000[0x360];
    s32 value;
} AiOwnerWord360;

s32 ai_clear_owner_word_360(AiActionContext *context) __asm__("func_800E7448");

s32 ai_clear_owner_word_360(AiActionContext *context)
{
    ((AiOwnerWord360 *)context->owner)->value = 0;
    return -1;
}
