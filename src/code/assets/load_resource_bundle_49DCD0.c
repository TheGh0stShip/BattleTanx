#include "resource_bundle_common.h"

extern u8 gBundle49DCD0Start[] __asm__("D_B049DCD0");
extern u8 gBundle49DCD0End[] __asm__("D_B04AC150");
extern s32 gResourceFadeNibble __asm__("D_80125794");
extern void func_80079BB4(s32 arg0);
extern void func_80079BF4(s32 arg0);
extern void func_801053B0(s32 arg0);

void load_resource_bundle_49DCD0(void) __asm__("func_800C54F0");

void load_resource_bundle_49DCD0(void)
{
    u32 size = gBundle49DCD0End - gBundle49DCD0Start;

    rom_dma_read((u32)gBundle49DCD0Start, gResourceScratch, size);
    lzari_decode(size, gResourceScratch, RESOURCE_BUNDLE_CAPACITY, gResourceTarget);
    func_80079BB4(6);
    func_80079BF4((gResourceFadeNibble << 28) >> 16);
    func_801053B0(1);
}
