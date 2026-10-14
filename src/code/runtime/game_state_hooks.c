#include "types.h"
extern s32 D_80134E5C;
void game_state_hook_noop(void) __asm__("func_8007AADC");
s32 get_pending_game_state(void) __asm__("func_8007AAE4");
void game_state_hook_noop(void) {}
s32 get_pending_game_state(void) { return D_80134E5C; }
