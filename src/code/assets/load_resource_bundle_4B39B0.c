#include "resource_bundle_common.h"

extern u8 gBundle4B39B0Start[] __asm__("D_B04B39B0");
extern u8 gBundle4B39B0End[] __asm__("D_B04B4B00");
extern void func_801053B0(s32 arg0);

void load_resource_bundle_4B39B0(void) __asm__("func_800CC470");

void load_resource_bundle_4B39B0(void)
{
    u32 size = gBundle4B39B0End - gBundle4B39B0Start;

    rom_dma_read((u32)gBundle4B39B0Start, gResourceScratch, size);
    lzari_decode(size, gResourceScratch, RESOURCE_BUNDLE_CAPACITY, gResourceTarget);
    func_801053B0(1);
}
