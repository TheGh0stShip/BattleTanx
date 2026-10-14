#include "resource_bundle_common.h"

extern u8 gBundle3D16D0Start[] __asm__("D_B03D16D0");
extern u8 gBundle3D16D0End[] __asm__("D_B03D6940");
extern s32 gControllerSlotCount __asm__("D_80134E58");
extern s32 gMenuState0 __asm__("D_803283C0");
extern s32 gMenuState1 __asm__("D_803283C4");
extern s32 gMenuOption0 __asm__("D_80328400");
extern s32 D_801262C0[4];
extern s32 D_803283C8[4];
extern s32 D_803283D8[4];
extern s32 D_803283E8;
extern s32 D_803283F0[4];
extern s32 func_800D9024(void);

void load_resource_bundle_3D16D0(void) __asm__("func_800D6908");

void load_resource_bundle_3D16D0(void)
{
    u32 size = gBundle3D16D0End - gBundle3D16D0Start;
    s32 *option = &gMenuOption0;
    s32 i;

    rom_dma_read((u32)gBundle3D16D0Start, gResourceScratch, size);
    lzari_decode(size, gResourceScratch, RESOURCE_BUNDLE_CAPACITY, gResourceTarget);
    D_803283E8 = -2;
    gMenuState1 = 0;
    for (i = 0; i < 4; i++) {
        D_803283F0[i] = 0;
        if (i < gControllerSlotCount) {
            D_803283C8[i] = 0;
            gMenuState1++;
        } else if (option[i] < 4) {
            D_803283D8[i] = 1;
            D_801262C0[i] = 3;
            gMenuState1++;
        } else {
            option[i] = 4;
            D_803283D8[i] = 2;
            D_801262C0[i] = 4;
        }
    }
    gMenuState0 = func_800D9024();
}
