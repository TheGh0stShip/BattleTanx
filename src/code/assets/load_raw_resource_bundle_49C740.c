#include "resource_bundle_common.h"

/* The one uncompressed bundle is copied straight into the target when it
 * fits in 0x3A980 bytes. */
extern u8 gBundle49C740Start[] __asm__("D_B049C740");
extern u8 gBundle49C740End[] __asm__("D_B049DCD0");
extern s32 gBundleWord __asm__("D_80327F40");
extern u8 gBundleReady __asm__("D_80327F44");
extern s32 gResourceFadeNibble __asm__("D_80125794");
extern void func_80079BB4(s32 arg0);
extern void func_80079BF4(s32 arg0);
extern void func_801053B0(s32 arg0);

void load_raw_resource_bundle_49C740(void) __asm__("func_800CA980");

void load_raw_resource_bundle_49C740(void)
{
    u32 size = gBundle49C740End - gBundle49C740Start;

    if (size <= 0x3A980) {
        rom_dma_read((u32)gBundle49C740Start, gResourceTarget, size);
        func_801053B0(1);
        gBundleWord = 0;
        gBundleReady = 1;
        func_80079BB4(6);
        func_80079BF4((gResourceFadeNibble << 28) >> 16);
    }
}
