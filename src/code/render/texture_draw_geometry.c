#include "types.h"

extern s32 gTextureDrawX __asm__("D_803AAD88");
extern s32 gTextureDrawY __asm__("D_803AAD8C");
extern f32 gTextureDrawScaleX __asm__("D_803AAD90");
extern f32 gTextureDrawScaleY __asm__("D_803AAD94");
extern u8 gTextureDrawRed __asm__("D_803B75A4");
extern u8 gTextureDrawGreen __asm__("D_803B75A5");
extern u8 gTextureDrawBlue __asm__("D_803B75A6");
extern u8 gTextureDrawAlpha __asm__("D_803B75A7");

void set_texture_draw_position(s32 x, s32 y) __asm__("func_8010552C");
void set_texture_draw_scale(f32 x, f32 y) __asm__("func_80105544");
void set_texture_draw_color(u8 red, u8 green, u8 blue, u8 alpha) __asm__("func_8010555C");

void set_texture_draw_position(s32 x, s32 y)
{
    gTextureDrawX = x;
    gTextureDrawY = y;
}

void set_texture_draw_scale(f32 x, f32 y)
{
    gTextureDrawScaleX = x;
    gTextureDrawScaleY = y;
}

void set_texture_draw_color(u8 red, u8 green, u8 blue, u8 alpha)
{
    gTextureDrawRed = red;
    gTextureDrawGreen = green;
    gTextureDrawBlue = blue;
    gTextureDrawAlpha = alpha;
}
