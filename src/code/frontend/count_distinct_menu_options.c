#include "types.h"

extern s32 gMenuOptions[4] __asm__("D_80328400");

s32 count_distinct_menu_options(void) __asm__("func_800D9024");

s32 count_distinct_menu_options(void)
{
    s32 count = 0;
    s32 value;
    s32 i;

    for (value = 0; value < 4; value++) {
        for (i = 0; i < 4; i++) {
            if (gMenuOptions[i] == value) {
                count++;
                break;
            }
        }
    }
    return count;
}
