#include "resource_bundle_common.h"

extern u8 gBundle4B3280Start[] __asm__("D_B04B3280");
extern u8 gBundle4B3280End[] __asm__("D_B04B39B0");
extern u8 gBundle4B3280Flag __asm__("D_80328280");
extern void func_801053B0(s32 arg0);

void load_resource_bundle_4B3280(void) __asm__("func_800D0D30");

void load_resource_bundle_4B3280(void)
{
    u32 size;

    func_801053B0(1);
    size = gBundle4B3280End - gBundle4B3280Start;
    rom_dma_read((u32)gBundle4B3280Start, gResourceScratch, size);
    lzari_decode(size, gResourceScratch, RESOURCE_BUNDLE_CAPACITY, gResourceTarget);
    gBundle4B3280Flag = 0;
}
