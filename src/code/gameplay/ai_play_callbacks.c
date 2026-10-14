#include "types.h"

typedef struct AiPlayTarget {
    u8 pad00[0x14];
    u16 flags;
} AiPlayTarget;

typedef struct AiPlayContext {
    u8 pad00[0x4];
    AiPlayTarget *target;
    u8 pad08[0x8];
    s32 currentPlay;
    s32 candidatePlay;
    u8 pad18[0x8];
    f32 params[8];
    s32 paramCount;
} AiPlayContext;

void ai_push_param(AiPlayContext *context, f32 value) __asm__("func_800E9A00");
s32 ai_play_null_callback(AiPlayContext *context) __asm__("func_800E9A20");
s32 ai_play_eai_twist_callback(AiPlayContext *context) __asm__("func_800E9A28");
f32 ai_score_keep_current_play(AiPlayContext *context) __asm__("func_800E9A30");
f32 ai_score_current_play_or_target_flag(AiPlayContext *context) __asm__("func_800E9A54");

void ai_push_param(AiPlayContext *context, f32 value)
{
    context->params[context->paramCount] = value;
    context->paramCount++;
}

s32 ai_play_null_callback(AiPlayContext *context)
{
    return 0;
}

s32 ai_play_eai_twist_callback(AiPlayContext *context)
{
    return 0;
}

f32 ai_score_keep_current_play(AiPlayContext *context)
{
    if (context->currentPlay == context->candidatePlay) {
        return 1.0f;
    }
    return 0.0f;
}

f32 ai_score_current_play_or_target_flag(AiPlayContext *context)
{
    if (context->currentPlay == context->candidatePlay) {
        return 1.0f;
    }
    if (context->target->flags & 4) {
        return 1.0f;
    }
    return 0.0f;
}
