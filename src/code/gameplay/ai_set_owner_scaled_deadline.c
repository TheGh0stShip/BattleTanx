#include "types.h"

typedef struct AiDeadlineOwner {
    u8 pad00[0x360];
    s32 value360;
} AiDeadlineOwner;

typedef struct AiDeadlineContext {
    u8 pad00[0x8];
    AiDeadlineOwner *value08;
    u8 pad0C[0x14];
    f32 value20;
} AiDeadlineContext;

extern s32 get_elapsed_game_ticks(void) __asm__("func_8007B1DC");
extern f32 D_800746E8;
extern f32 D_800746EC;

s32 ai_set_owner_scaled_deadline(AiDeadlineContext *context) __asm__("func_800E73E0");

s32 ai_set_owner_scaled_deadline(AiDeadlineContext *context) {
    f32 amount = context->value20;
    s32 now = get_elapsed_game_ticks();
    s32 delay = (amount * D_800746E8) / D_800746EC;

    context->value08->value360 = now + delay;
    return -1;
}
