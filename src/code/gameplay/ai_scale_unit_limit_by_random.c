#include "types.h"

typedef struct AiUnit {
    u8 pad00[0x1C];
    s32 value1C;
    u8 pad20[0x33C];
    u16 value35C;
} AiUnit;

typedef struct AiContext {
    u8 pad00[8];
    AiUnit *unit;
    u8 pad0C[0x14];
    f32 minScale;
    f32 maxScale;
} AiContext;

extern f32 func_800E9720(AiContext *context, s32 range) __asm__("func_800E9720");
extern f32 D_800746F0;
extern f32 D_800746F4;

s32 ai_scale_unit_limit_by_random(AiContext *context) __asm__("func_800E7490");

s32 ai_scale_unit_limit_by_random(AiContext *context) {
    f32 lo = context->minScale;
    f32 span = context->maxScale - lo;
    f32 r = func_800E9720(context, 0x1000);
    f32 value = context->unit->value1C;
    f32 scale = lo + span * (1.0f - r);

    if (1000.0f < value) {
        context->unit->value35C = 1000;
    } else {
        context->unit->value35C = value * scale;
    }
    return -1;
}
