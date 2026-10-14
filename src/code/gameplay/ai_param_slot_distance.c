#include "types.h"

typedef struct AiSlotDistance {
    u8 pad00[0x8];
    f32 value08;
} AiSlotDistance;

typedef struct AiParamOwner {
    u8 pad000[0x359];
    u8 slot;
} AiParamOwner;

typedef struct AiParamSlotContext {
    u8 pad00[0x8];
    AiParamOwner *owner;
    u8 pad0C[0xC];
    s16 index;
} AiParamSlotContext;

extern AiSlotDistance *func_800E52A0(s16, u8);
extern f32 D_80074870;
extern f32 D_80074874;

f32 ai_param_slot_distance(AiParamSlotContext *context) __asm__("func_800E9480");

f32 ai_param_slot_distance(AiParamSlotContext *context)
{
    u8 slot = context->owner->slot;

    if (slot == 0xFF) {
        return D_80074874;
    }
    return func_800E52A0(context->index, slot)->value08 * D_80074870;
}
