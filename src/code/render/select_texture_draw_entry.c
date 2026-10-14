#include "types.h"

typedef struct TextureDrawTable {
    s32 header;
    s32 offsets[1];
} TextureDrawTable;

extern s32 gTextureDrawEntryCount __asm__("D_803AAD80");
extern s32 gTextureDrawEntry __asm__("D_803AAD84");
extern u8 *gTextureDrawEntryData __asm__("D_803AAD98");
extern TextureDrawTable *gTextureDrawTable __asm__("D_803AAD9C");
extern u8 gTextureDrawData[] __asm__("D_803AADA0");

void select_texture_draw_entry(s32 index) __asm__("func_801054E0");

void select_texture_draw_entry(s32 index)
{
    if (index >= gTextureDrawEntryCount) {
        index = 0;
    }
    gTextureDrawEntry = index;
    gTextureDrawEntryData = gTextureDrawTable->offsets[index] + gTextureDrawData;
}
