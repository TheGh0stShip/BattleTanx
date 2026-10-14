#include "types.h"

typedef struct BankInstrumentList {
    u8 pad00[0xC];
    s32 value0C;
} BankInstrumentList;

typedef struct BankFile {
    u8 pad00[0x4];
    BankInstrumentList *value04;
} BankFile;

extern void rom_dma_read(u8 *romAddress, void *destination, u32 size) __asm__("func_80077930");
extern void alBnkfNew(BankFile *file, u8 *table) __asm__("func_80110AB4");
extern void *alHeapDBAlloc(u8 *file, s32 line, void *heap, s32 num, s32 size) __asm__("func_80112140");
extern u8 gAudioHeap[] __asm__("D_80150340");
extern u32 gSequenceRomOffsets[] __asm__("D_80125718");
extern void *gSequenceBuffer __asm__("D_80150384");
extern BankFile *D_80150388;
extern BankFile *D_8015038C;
extern s32 D_80150390;
extern u8 D_B0100000[];
extern u8 D_B0215620[];
extern u8 gPrimaryBankRomEnd[] __asm__("D_B0217EC0");
extern u8 gSecondaryTableRomStart[] __asm__("D_B0217EC0");
extern u8 D_B0298D60[];
extern u8 D_B029A710[];

void load_audio_banks(void) __asm__("func_8007A004");

void load_audio_banks(void) {
    s32 i;
    u32 maxSize;
    u32 entrySize;

    D_80150388 = alHeapDBAlloc(0, 0, gAudioHeap, 1, gPrimaryBankRomEnd - D_B0215620);
    rom_dma_read(D_B0215620, D_80150388, gPrimaryBankRomEnd - D_B0215620);
    alBnkfNew(D_80150388, D_B0100000);
    D_80150390 = D_80150388->value04->value0C;
    D_8015038C = alHeapDBAlloc(0, 0, gAudioHeap, 1, D_B029A710 - D_B0298D60);
    rom_dma_read(D_B0298D60, D_8015038C, D_B029A710 - D_B0298D60);
    alBnkfNew(D_8015038C, gSecondaryTableRomStart);
    maxSize = 0;
    for (i = 0; i < 19; i++) {
        entrySize = gSequenceRomOffsets[i] - (&gSequenceRomOffsets[-1])[i];
        if (entrySize < maxSize) {
            entrySize = maxSize;
        }
        maxSize = entrySize;
    }
    gSequenceBuffer = alHeapDBAlloc(0, 0, gAudioHeap, 1, maxSize);
}
