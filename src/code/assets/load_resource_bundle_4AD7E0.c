#include "resource_bundle_common.h"

extern u8 gBundle4AD7E0Start[] __asm__("D_B04AD7E0");
extern u8 gBundle4AD7E0End[] __asm__("D_B04B1300");
extern s32 gBundle4AD7E0Values[4] __asm__("D_80328290");

void load_resource_bundle_4AD7E0(void) __asm__("func_800D44CC");

void load_resource_bundle_4AD7E0(void)
{
    u32 size = gBundle4AD7E0End - gBundle4AD7E0Start;

    rom_dma_read((u32)gBundle4AD7E0Start, gResourceScratch, size);
    lzari_decode(size, gResourceScratch, RESOURCE_BUNDLE_CAPACITY, gResourceTarget);
    gBundle4AD7E0Values[3] = 10;
    gBundle4AD7E0Values[2] = 10;
    gBundle4AD7E0Values[1] = 10;
    gBundle4AD7E0Values[0] = 10;
}
