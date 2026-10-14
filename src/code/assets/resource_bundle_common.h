#ifndef RESOURCE_BUNDLE_COMMON_H
#define RESOURCE_BUNDLE_COMMON_H

#include "types.h"

/* LZARI-compressed resource bundles live in cartridge ROM between linker
 * segment symbols (PI addresses 0xB0000000 + ROM offset).  A loader reads a
 * segment into a scratch buffer and expands it into the shared resource
 * target; 0x25800 is the destination capacity passed to the decoder.  A
 * decompressed bundle is u32 count, u32 payload offset, u32 boundary[count]
 * (see tools/battletanx_assets.py). */
#define RESOURCE_BUNDLE_CAPACITY 0x25800

extern u8 gResourceScratch[] __asm__("D_803DA800");
extern void *gResourceTarget __asm__("D_803275F4");

extern void rom_dma_read(u32 romAddress, void *destination, u32 size) __asm__("func_80077930");
extern s32 lzari_decode(u32 sourceSize, u8 *source, u32 destinationSize, u8 *destination)
    __asm__("func_800F4F60");

#endif
