#include "resource_bundle_common.h"

/* Ten strip bundles, addressed by parallel ROM start/end tables, expand to
 * consecutive 0xBC00-byte slots after the first 0xA000 bytes of the target;
 * each is loaded at most once. */
#define STRIP_BUNDLE_CAPACITY 0xBC00

extern u8 gStripBundleLoaded[] __asm__("D_80327F30");
extern u8 *gStripBundleRomStart[] __asm__("D_80134B88");
extern u8 *gStripBundleRomEnd[] __asm__("D_80134BB0");

void load_strip_bundle(s32 index) __asm__("func_800CA8C0");

void load_strip_bundle(s32 index)
{
    u32 size;

    if (gStripBundleLoaded[index] == 0) {
        gStripBundleLoaded[index] = 1;
        size = gStripBundleRomEnd[index] - gStripBundleRomStart[index];
        rom_dma_read((u32)gStripBundleRomStart[index], gResourceScratch, size);
        lzari_decode(size, gResourceScratch, STRIP_BUNDLE_CAPACITY,
                                (u8 *)gResourceTarget + 0xA000 + index * STRIP_BUNDLE_CAPACITY);
    }
}
