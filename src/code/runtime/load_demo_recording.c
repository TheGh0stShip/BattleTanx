#include "types.h"

typedef struct DemoHeader {
    s32 frameCount;
    s32 objectCount;
    s32 value08;
    s32 trailerCount;
    s32 value10;
    s32 value14;
} DemoHeader;

extern void rom_dma_read(u8 *romAddress, void *destination, s32 size) __asm__("func_80077930");
extern u8 *allocate_runtime_memory(s32 size) __asm__("func_80081A78");
extern void start_demo_playback(void) __asm__("func_800ECBA8");

extern s32 gDemoIndex __asm__("D_80137904");
extern s32 gDemoActive __asm__("D_80137900");
extern DemoHeader gDemoHeader __asm__("D_8033B600");
extern s32 gDemoFrame __asm__("D_8033B5F0");
extern s32 gDemoFrameSize __asm__("D_8033B5F4");
extern u8 *gDemoData __asm__("D_8033B618");
extern u8 *gDemoCursor __asm__("D_8033B61C");
extern u8 *gDemoTrailer __asm__("D_8033B620");
extern s32 gDemoTrailerIndex __asm__("D_8033B624");
extern s32 gDemoTrailerTarget __asm__("D_8033B628");
extern u8 D_B0319B30[];
extern u8 D_B0334630[];
extern u8 D_B0348DB0[];
extern u8 D_B0364100[];
extern u8 D_B03747F0[];
extern u8 D_B0380670[];
extern u8 D_B0383CC0[];
extern u8 D_B038BBE0[];
extern u8 D_B03A0820[];
extern u8 D_B03B9630[];
extern u8 D_B03C1550[];

s32 load_demo_recording(void) __asm__("func_800EC410");

s32 load_demo_recording(void) {
    u8 *rom;
    s32 i;

    switch (gDemoIndex) {
    case 1:
        rom = D_B0334630;
        break;
    case 2:
        rom = D_B0348DB0;
        break;
    case 4:
        rom = D_B03747F0;
        break;
    case 5:
        rom = D_B0380670;
        break;
    case 6:
        rom = D_B0383CC0;
        break;
    case 7:
        rom = D_B038BBE0;
        break;
    case 8:
        rom = D_B03A0820;
        break;
    case 9:
        rom = D_B03B9630;
        break;
    case 10:
        rom = D_B03C1550;
        break;
    case 3:
    case 11:
        rom = D_B0364100;
        break;
    case 0:
    default:
        rom = D_B0319B30;
        break;
    }
    rom_dma_read(rom, &gDemoHeader, sizeof(DemoHeader));
    gDemoFrameSize = gDemoHeader.objectCount * 12 + 0x30;
    gDemoData = allocate_runtime_memory(gDemoFrameSize * gDemoHeader.frameCount + gDemoHeader.trailerCount * 12);
    if (gDemoData == 0) {
        return -1;
    }
    rom_dma_read(rom + sizeof(DemoHeader), gDemoData,
                 gDemoFrameSize * gDemoHeader.frameCount + gDemoHeader.trailerCount * 12);
    gDemoFrame = 0;
    gDemoTrailerIndex = 0;
    gDemoActive = 1;
    gDemoCursor = gDemoData;
    gDemoTrailer = gDemoData + gDemoFrameSize * gDemoHeader.frameCount;
    for (i = 0; i < gDemoHeader.trailerCount; i++) {
    }
    if (gDemoHeader.trailerCount == 0) {
        gDemoTrailerIndex = -1;
    }
    gDemoTrailerTarget = -1;
    start_demo_playback();
    return 0;
}
