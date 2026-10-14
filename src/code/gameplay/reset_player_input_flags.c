#include "types.h"

extern s16 D_801B4A96;
extern void refresh_player_inputs(s32 value) __asm__("func_80079B08");

void reset_player_input_flags(s32 unused) __asm__("func_8007963C");

void reset_player_input_flags(s32 unused)
{
    s16 *flag;
    s32 i;
    s16 value;

    value = 1;
    i = 31;
    flag = &D_801B4A96;
    do {
        *flag = value;
        i--;
        flag--;
    } while (i >= 0);
    refresh_player_inputs(unused);
}
