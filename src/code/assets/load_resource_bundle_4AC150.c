#include "resource_bundle_common.h"

extern u8 gBundle4AC150Start[] __asm__("D_B04AC150");
extern u8 gBundle4AC150End[] __asm__("D_B04AD7E0");
extern void func_801053B0(s32 arg0);

void load_resource_bundle_4AC150(void) __asm__("func_800DADBC");

void load_resource_bundle_4AC150(void)
{
    u32 size = gBundle4AC150End - gBundle4AC150Start;

    rom_dma_read((u32)gBundle4AC150Start, gResourceScratch, size);
    lzari_decode(size, gResourceScratch, RESOURCE_BUNDLE_CAPACITY, gResourceTarget);
    func_801053B0(1);
}
