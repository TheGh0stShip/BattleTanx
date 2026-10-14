#include "types.h"

typedef struct AiStepContext {
    u8 pad00[0x8];
    s32 value08;
    u8 *value0C;
    u8 pad10[0x8];
    s16 value18;
} AiStepContext;

extern void ai_target_set_unit(void *target, s16 fromId, s16 toId) __asm__("func_800E34B4");
extern void ai_target_set_value(void *target, s32 value) __asm__("func_800E3A64");
extern s16 ai_find_target_unit(AiStepContext *ctx, void *table, s32 *found) __asm__("func_800E3CF0");
extern u8 D_80135878[];

s32 ai_step_select_target_unit(AiStepContext *ctx) __asm__("func_800E6B3C");

s32 ai_step_select_target_unit(AiStepContext *ctx)
{
    s32 found;
    s16 id;

    id = ai_find_target_unit(ctx, D_80135878, &found);
    if (id == 0xFF) {
        if (found != 0) {
            ai_target_set_value(ctx->value0C + 0x18, ctx->value08);
        }
    } else {
        ai_target_set_unit(ctx->value0C + 0x18, ctx->value18, id);
    }
    return -1;
}
