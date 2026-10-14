#include "types.h"

typedef struct AiParameterContext AiParameterContext;
typedef f32 (*AiParameterProvider)(AiParameterContext *context);

typedef struct AiParameterOwner {
    u8 pad000[0x190];
    f32 values[1];
} AiParameterOwner;

typedef struct AiParameterMember {
    u8 pad000[0x10C];
    f32 values[1];
} AiParameterMember;

struct AiParameterContext {
    u8 pad00[0x4];
    AiParameterOwner *owner;
    AiParameterMember *member;
};

extern AiParameterProvider D_801358C0[];
extern AiParameterProvider D_80135920[];
extern AiParameterProvider D_80135980[];

f32 ai_get_parameter(AiParameterContext *context, s32 key) __asm__("func_800E9720");

f32 ai_get_parameter(AiParameterContext *context, s32 key) {
    if (key & 0x1000) {
        if (key & 0x100) {
            return D_80135980[key & 0xFF](context);
        }
        return context->member->values[key & 0xFF];
    }
    if (key & 0x2000) {
        if (key & 0x100) {
            return D_80135920[key & 0xFF](context);
        }
        return context->owner->values[key & 0xFF];
    }
    if (key & 0x8000) {
        return D_801358C0[key & 0xFF](context);
    }
    return 0.0f;
}
