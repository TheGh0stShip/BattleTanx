#include "types.h"

typedef struct Gfx {
    u32 w0;
    u32 w1;
} Gfx;

typedef struct PalettedImage {
    u8 pad00[4];
    s32 paletteOffset;
} PalettedImage;

#define GFX_COMMAND(packet, first, second) { \
    Gfx *command = (packet); \
    command->w0 = (first); \
    command->w1 = (second); \
}

extern Gfx *gFrontendDisplayList __asm__("D_803276D4");
extern s32 gResourceTarget __asm__("D_803275F4");

extern void draw_paletted_image(Gfx **list, u8 *texels, s32 arg2, s32 arg3, s32 width, s32 height, s32 tileWidth,
                                s32 tileHeight, s32 x, s32 y, s32 width2, s32 height2, s32 s, s32 t,
                                f32 scaleX, f32 scaleY) __asm__("func_800F3D40");

void draw_resource_ci8_image(void) __asm__("func_800C4090");

void draw_resource_ci8_image(void) {
    GFX_COMMAND(gFrontendDisplayList++, 0xB900031DU, 0x00504240);
    GFX_COMMAND(gFrontendDisplayList++, 0xBA000E02U, 0x8000);
    GFX_COMMAND(gFrontendDisplayList++, 0xFC119623U, 0xFF2FFFFFU);
    GFX_COMMAND(gFrontendDisplayList++, 0xFA000101U, 0xFFFFFFFFU);
    GFX_COMMAND(gFrontendDisplayList++, 0xFD100000U,
                ((PalettedImage *)gResourceTarget)->paletteOffset + gResourceTarget);
    GFX_COMMAND(gFrontendDisplayList++, 0xE8000000U, 0);
    GFX_COMMAND(gFrontendDisplayList++, 0xF5000100U, 0x07000000);
    GFX_COMMAND(gFrontendDisplayList++, 0xE6000000U, 0);
    GFX_COMMAND(gFrontendDisplayList++, 0xF0000000U, 0x073FC000);
    GFX_COMMAND(gFrontendDisplayList++, 0xE7000000U, 0);
    draw_paletted_image(&gFrontendDisplayList,
                        (u8 *)(((PalettedImage *)gResourceTarget)->paletteOffset + gResourceTarget + 0x200),
                        2, 1, 0x114, 0xD2, 0x20, 0x20, 0x16, 0xF, 0x114, 0xD2, 0, 0, 1.0f, 1.0f);
}
