#include "resource_bundle_common.h"

extern u8 gBundle3DFD10Start[] __asm__("D_B03DFD10");
extern u8 gBundle3DFD10End[] __asm__("D_B03EA970");
extern s32 D_80134E58;
extern s32 D_80134E5C;
extern s32 D_80328410;
extern void func_801053B0(s32 arg0);

void load_resource_bundle_3DFD10(void) __asm__("func_800D9080");

void load_resource_bundle_3DFD10(void)
{
    u32 size = gBundle3DFD10End - gBundle3DFD10Start;

    rom_dma_read((u32)gBundle3DFD10Start, gResourceScratch, size);
    lzari_decode(size, gResourceScratch, RESOURCE_BUNDLE_CAPACITY, gResourceTarget);
    func_801053B0(1);
    if (D_80134E5C == 0) {
        D_80328410 = 0x1C;
    } else {
        D_80328410 = D_80134E58 >= 3 ? 6 : 8;
    }
}
