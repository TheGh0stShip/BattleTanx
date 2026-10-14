#include "types.h"

extern s32 *get_game_mode(void) __asm__("func_8007AAF4");
extern s16 D_80125A30[];

s16 get_mode_halfword(void) __asm__("func_80086AE8");

s16 get_mode_halfword(void)
{
    return D_80125A30[get_game_mode()[1]];
}
