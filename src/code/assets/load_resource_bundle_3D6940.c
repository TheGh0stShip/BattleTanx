#include "resource_bundle_common.h"

extern u8 gBundle3D6940Start[] __asm__("D_B03D6940");
extern u8 gBundle3D6940End[] __asm__("D_B03DC430");
extern s32 D_80327ED0;
extern s32 D_80327ED4;
extern s32 D_80327ED8;
extern u8 D_80327EDC;
extern s32 D_80327EE0;
extern s32 D_80327EE4;
extern s32 D_80327EE8;
extern s32 D_80327EEC;
extern s32 D_80327EF0;
extern void func_800C80E0(void);
extern void func_801053B0(s32 arg0);

void load_resource_bundle_3D6940(void) __asm__("func_800C5B90");

void load_resource_bundle_3D6940(void)
{
    u32 size = gBundle3D6940End - gBundle3D6940Start;

    D_80327ED8 = -1;
    D_80327EE4 = -1;
    D_80327EEC = 0xFF;
    D_80327ED0 = 0;
    D_80327ED4 = 0;
    D_80327EDC = 0;
    D_80327EE0 = 0;
    D_80327EE8 = 0;
    D_80327EF0 = 0xF;
    rom_dma_read((u32)gBundle3D6940Start, gResourceScratch, size);
    lzari_decode(size, gResourceScratch, RESOURCE_BUNDLE_CAPACITY, gResourceTarget);
    func_800C80E0();
    func_801053B0(1);
}
