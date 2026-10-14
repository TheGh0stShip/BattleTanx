#include "types.h"

typedef struct TextureDrawTable {
    s32 header;
    s32 offsets[1];
} TextureDrawTable;

extern void rom_dma_read(u32 romAddress, void *destination, u32 size) __asm__("func_80077930");
extern s32 gTextureDrawEntryCount __asm__("D_803AAD80");
extern s32 gTextureDrawEntry __asm__("D_803AAD84");
extern s32 gTextureDrawX __asm__("D_803AAD88");
extern s32 gTextureDrawY __asm__("D_803AAD8C");
extern f32 gTextureDrawScaleX __asm__("D_803AAD90");
extern f32 gTextureDrawScaleY __asm__("D_803AAD94");
extern u8 *gTextureDrawEntryData __asm__("D_803AAD98");
extern TextureDrawTable *gTextureDrawTable __asm__("D_803AAD9C");
extern u8 gTextureDrawData[] __asm__("D_803AADA0");
extern s32 D_803B75A0;
extern u8 gTextureDrawRed __asm__("D_803B75A4");
extern u8 gTextureDrawGreen __asm__("D_803B75A5");
extern u8 gTextureDrawBlue __asm__("D_803B75A6");
extern u8 gTextureDrawAlpha __asm__("D_803B75A7");
extern u8 gTextureDrawOption __asm__("D_803B75A9");
extern s32 gTextureDrawMode __asm__("D_803B75AC");
extern f32 D_80075420;
extern u8 D_B02C3E50[];
extern u8 D_B02CB230[];
extern u8 D_B02D2790[];

void load_texture_draw_font(u8 font) __asm__("func_801053B0");

void load_texture_draw_font(u8 font)
{
    TextureDrawTable *table;

    gTextureDrawMode = 8;
    gTextureDrawEntry = 0;
    gTextureDrawX = 0;
    gTextureDrawY = 0;
    gTextureDrawOption = 0;
    D_803B75A0 = 1;
    gTextureDrawRed = 0xFF;
    gTextureDrawGreen = 0xFF;
    gTextureDrawBlue = 0xFF;
    gTextureDrawAlpha = 0xFF;
    gTextureDrawScaleX = D_80075420;
    gTextureDrawScaleY = D_80075420;
    if (font == 1) {
        rom_dma_read((u32)D_B02CB230, gTextureDrawData, D_B02D2790 - D_B02CB230);
    } else if (font == 0) {
        rom_dma_read((u32)D_B02C3E50, gTextureDrawData, D_B02CB230 - D_B02C3E50);
    }
    table = (TextureDrawTable *)gTextureDrawData;
    gTextureDrawTable = table;
    gTextureDrawEntryCount = table->header;
    gTextureDrawEntryData = table->offsets[0] + gTextureDrawData;
}
