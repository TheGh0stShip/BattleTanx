#include "resource_bundle_common.h"

extern u8 gBundle4B1300Start[] __asm__("D_B04B1300");
extern u8 gBundle4B1300End[] __asm__("D_B04B3280");
extern s32 D_80328150;
extern s32 D_80328154;
extern u8 D_80328158;
extern u8 D_80328159;
extern u8 D_8032815A;
extern s32 D_80328170;
extern void func_801053B0(s32 arg0);

void load_resource_bundle_4B1300(void) __asm__("func_800CE4B0");

void load_resource_bundle_4B1300(void)
{
    u32 size = gBundle4B1300End - gBundle4B1300Start;

    rom_dma_read((u32)gBundle4B1300Start, gResourceScratch, size);
    lzari_decode(size, gResourceScratch, RESOURCE_BUNDLE_CAPACITY, gResourceTarget);
    func_801053B0(1);
    D_80328150 = 0;
    D_80328158 = 0;
    D_80328159 = 0;
    D_8032815A = 0;
    D_80328154 = 0;
    D_80328170 = 0;
}
