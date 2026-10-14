#include "types.h"

extern u8 gTextureDrawOption __asm__("D_803B75A9");
extern s32 gTextureDrawMode __asm__("D_803B75AC");

void set_texture_draw_mode(s32 mode) __asm__("func_801054C0");
void set_texture_draw_option(u8 option) __asm__("func_801054D0");

void set_texture_draw_mode(s32 mode)
{
    gTextureDrawMode = mode;
}

void set_texture_draw_option(u8 option)
{
    gTextureDrawOption = option;
}
