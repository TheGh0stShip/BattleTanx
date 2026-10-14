#include "types.h"

extern s32 gDifficultyLevel __asm__("D_801B4AB4");
extern s32 gEntityCapacity __asm__("D_801B4AB8");

extern void initialize_runtime_state(void) __asm__("func_8007AB04");
extern void set_runtime_mode(s32 mode) __asm__("func_8007AC20");
extern void clear_callback_state(void) __asm__("func_8007C298");

void initialize_game_runtime(void) __asm__("func_8007AA70");
s32 get_difficulty_level(void) __asm__("func_8007AAA0");
s32 get_entity_capacity(void) __asm__("func_8007AAB0");

void initialize_game_runtime(void)
{
    initialize_runtime_state();
    set_runtime_mode(0);
    clear_callback_state();
}

s32 get_difficulty_level(void)
{
    return gDifficultyLevel;
}

s32 get_entity_capacity(void)
{
    return gEntityCapacity;
}
