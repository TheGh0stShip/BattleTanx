#include "ai_action_helpers.h"

typedef struct AiControllerFlags {
    u8 pad000[0x1A4];
    u8 active;
    u8 requested;
} AiControllerFlags;

s32 ai_invert_controller_flag(AiActionContext *context) __asm__("func_800E70C4");

s32 ai_invert_controller_flag(AiActionContext *context)
{
    AiControllerFlags *controller = context->controller;
    controller->active = !controller->requested;
    return -1;
}
