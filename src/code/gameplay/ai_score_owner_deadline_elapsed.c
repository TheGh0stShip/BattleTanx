#include "types.h"

extern s32 get_elapsed_game_ticks(void) __asm__("func_8007B1DC");
extern f32 D_800748A4;
extern f32 D_800748A8;

typedef struct AiDeadlineOwner {
    u8 pad00[0x360];
    s32 value360;
} AiDeadlineOwner;

typedef struct AiDeadlineContext {
    u8 pad00[0x8];
    AiDeadlineOwner *value08;
} AiDeadlineContext;

f32 ai_score_owner_deadline_elapsed(AiDeadlineContext *context) __asm__("func_800E96C0");

f32 ai_score_owner_deadline_elapsed(AiDeadlineContext *context) {
    s32 deadline = context->value08->value360;
    f32 result;
    s32 now;

    if (deadline == 0) {
        return 0.0f;
    }
    now = get_elapsed_game_ticks();
    result = D_800748A4;
    if (now >= deadline) {
        result = D_800748A8;
    }
    return result;
}
