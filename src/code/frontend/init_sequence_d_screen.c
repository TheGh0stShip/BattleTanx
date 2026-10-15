#include "types.h"

extern u64 osGetTime(void) __asm__("func_801120A0");
extern void load_texture_draw_font(s32 font) __asm__("func_801053B0");
extern void rom_dma_read(u8 *romAddress, u8 *destination, s32 size) __asm__("func_80077930");
extern s32 lzari_decode(u32 sourceSize, u8 *source, u32 destinationSize, u8 *destination) __asm__("func_800F4F60");
extern u64 D_80145DA0;
extern s8 D_80132EF0;
extern u8 *D_803275F4;
extern u8 gSequenceDState __asm__("D_80327E50");
extern u64 D_80327E58;
extern s32 D_80327E60;
extern u8 D_80327EB1;
extern u8 D_80327EB2;
extern u8 gScreenCompressed[] __asm__("D_803DA800");
extern u8 D_B0596EA0[];
extern u8 D_B05A1110[];

void init_sequence_d_screen(void) __asm__("func_800C3F00");

void init_sequence_d_screen(void) {
    s32 size;

    size = D_B05A1110 - D_B0596EA0;
    rom_dma_read(D_B0596EA0, gScreenCompressed, size);
    lzari_decode(size, gScreenCompressed, 0x25800, D_803275F4);
    load_texture_draw_font(1);
    D_80327EB2 = 0;
    D_80327EB1 = 0;
    switch (gSequenceDState) {
    case 0:
        D_80327E58 = osGetTime() * 1000000 / D_80145DA0 + 12000000;
        D_80327E60 = 0xF0;
        break;
    case 4:
        D_80327EB1 = 1;
        gSequenceDState = 5;
        break;
    }
    D_80132EF0 = 1;
}
