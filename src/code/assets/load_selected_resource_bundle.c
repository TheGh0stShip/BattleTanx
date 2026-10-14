#include "resource_bundle_common.h"

extern s32 select_audio_mode(u32 mode) __asm__("func_800AB95C");
extern s16 D_80133FE0;
extern s32 D_80134010[];
extern u32 D_80134058[];
extern u32 D_80134080[];
extern s32 D_80327EE4;
extern s32 D_80327EE8;

void load_selected_resource_bundle(void) __asm__("func_800C80E0");

void load_selected_resource_bundle(void) {
    s32 previousMode;
    u32 romStart;
    u32 size;
    s32 bundle;

    if (D_80134010[D_80327EE8] >= 10) {
        D_80134010[D_80327EE8] = 0;
    }
    if (D_80134010[D_80327EE8] != D_80327EE4) {
        previousMode = select_audio_mode(4);
        bundle = D_80134010[D_80327EE8];
        size = D_80134080[bundle] - D_80134058[bundle];
        romStart = D_80134058[bundle];
        rom_dma_read(romStart, gResourceScratch, size);
        lzari_decode(size, gResourceScratch, RESOURCE_BUNDLE_CAPACITY, gResourceTarget);
        select_audio_mode(previousMode);
        D_80133FE0 = 0x40;
        D_80327EE4 = D_80134010[D_80327EE8];
    }
}
