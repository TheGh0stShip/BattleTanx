#include "types.h"
extern s16 D_801B4A96[];
void reset_halfword_slots(void) __asm__("func_8007968C");
void reset_halfword_slots(void)
{
    s32 value;
    s32 i;
    s16 *slot;

    value = 1;
    i = 31;
    slot = D_801B4A96;
    do {
        *slot = value;
        i--;
        slot--;
    } while (i >= 0);
}
