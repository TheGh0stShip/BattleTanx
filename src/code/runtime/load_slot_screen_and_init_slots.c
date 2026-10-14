#include "types.h"

extern void rom_dma_read(u8 *romAddress, u8 *destination, s32 size) __asm__("func_80077930");
extern s32 lzari_decode(u32 sourceSize, u8 *source, u32 destinationSize, u8 *destination) __asm__("func_800F4F60");
extern s32 gControllerSlotCount __asm__("D_80134E58");
extern u8 *gResourceTarget __asm__("D_803275F4");
extern u8 D_B03D16D0[];
extern u8 D_B03D6940[];
extern u8 D_803DA800[];
extern s32 D_803283C0;
extern s32 D_803283C4;
extern s32 D_803283C8[4];
extern s32 D_803283D8[4];
extern s32 D_803283E8;
extern s32 D_803283F0[4];
extern s32 D_80328400[4];
extern s32 D_801262C0[4];

void load_slot_screen_and_init_slots(void) __asm__("func_800D6A54");

void load_slot_screen_and_init_slots(void) {
    s32 size = D_B03D6940 - D_B03D16D0;
    s32 i;
    rom_dma_read(D_B03D16D0, D_803DA800, size);
    lzari_decode(size, D_803DA800, 0x25800, gResourceTarget);
    D_803283C4 = gControllerSlotCount < 2 ? 2 : gControllerSlotCount;
    D_803283C0 = gControllerSlotCount < 2 ? 2 : gControllerSlotCount;
    D_803283E8 = -2;
    for (i = 0; i < 4; i++) {
        D_803283F0[i] = 0;
        if (i < gControllerSlotCount) {
            D_80328400[i] = i;
            D_803283D8[i] = 0;
            D_803283C8[i] = 0;
            D_801262C0[i] = 1;
        } else {
            D_80328400[i] = 4;
            D_803283D8[i] = 2;
            D_801262C0[i] = 4;
        }
    }
    if (gControllerSlotCount == 1) {
        D_803283C0 = 2;
        D_803283D8[1] = gControllerSlotCount;
        D_80328400[1] = gControllerSlotCount;
        D_801262C0[1] = 3;
    }
}
