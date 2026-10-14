#include "types.h"

extern s32 gMenuGridBase __asm__("D_80134FD4");
extern s32 gMenuGridX __asm__("D_80134FD8");
extern s32 gMenuGridY __asm__("D_80134FDC");

void set_menu_grid_position(s32 column, s32 row) __asm__("func_800D3A7C");

void set_menu_grid_position(s32 column, s32 row)
{
    s32 x;

    x = gMenuGridBase + column * 6 + 15;
    gMenuGridX = x;
    gMenuGridY = x + row * 40 + 30;
}
