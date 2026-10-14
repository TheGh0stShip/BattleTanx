#include "types.h"

extern s32 gMenuState0 __asm__("D_803283C0");
extern s32 gMenuState1 __asm__("D_803283C4");
extern s32 gMenuOption0 __asm__("D_80328400");
extern s32 gMenuOption1 __asm__("D_80328404");
extern s32 gMenuSelection __asm__("D_801352A4");

void reset_menu_state(void) __asm__("func_800D68D0");

void reset_menu_state(void)
{
    gMenuState1 = 2;
    gMenuState0 = 2;
    gMenuOption0 = 0;
    gMenuOption1 = 1;
    gMenuSelection = 0;
}
