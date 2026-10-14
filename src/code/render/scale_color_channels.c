#include "types.h"

typedef struct ScaledColor {
    u8 pad00[0xC];
    u8 red;
    u8 green;
    u8 blue;
} ScaledColor;

void scale_color_channels(ScaledColor *color, f32 scale) __asm__("func_80086B48");

void scale_color_channels(ScaledColor *color, f32 scale)
{
    f32 scaledRed;
    f32 scaledGreen;
    f32 scaledBlue;
    u32 red;
    u32 green;
    u32 blue;

    scaledRed = color->red * scale;
    if (scaledRed > 255.0f) {
        red = 255;
    } else {
        red = scaledRed;
    }
    color->red = red;
    scaledGreen = color->green * scale;
    if (scaledGreen > 255.0f) {
        green = 255;
    } else {
        green = scaledGreen;
    }
    color->green = green;
    scaledBlue = color->blue * scale;
    if (scaledBlue > 255.0f) {
        blue = 255;
    } else {
        blue = scaledBlue;
    }
    color->blue = blue;
}
