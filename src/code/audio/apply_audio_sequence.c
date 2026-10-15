#include "types.h"

typedef struct SeqMarker {
    u8 pad00[0x10];
} SeqMarker;

typedef struct SeqBankFile {
    s16 revision;
    s16 bankCount;
    void *bankArray[1];
} SeqBankFile;

extern void rom_dma_read(u32 romAddress, void *destination, s32 size) __asm__("func_80077930");
extern void stop_sequence_player(void) __asm__("func_80079D58");
extern void alCSeqNew(void *seq, void *ptr, s32 len) __asm__("func_80119A78");
extern void alCSeqNewMarker(void *seq, SeqMarker *marker, s32 ticks) __asm__("func_80119748");
extern void alCSPLoop(void *seqp, SeqMarker *start, SeqMarker *end, s32 count) __asm__("func_8011B8B0");
extern void alCSPSetSeq(void *seqp, void *seq) __asm__("func_8011B960");
extern void alCSPSetBank(void *seqp, void *bank) __asm__("func_8011B920");
extern void alCSPPlay(void *seqp) __asm__("func_8011B8F0");

extern void *gAudioSequenceHandle __asm__("D_80150350");
extern void *gAudioSequence __asm__("D_80150354");
extern void *gSequenceBuffer __asm__("D_80150384");
extern SeqBankFile *D_8015038C;
extern u32 gSequenceRomOffsets[] __asm__("D_80125718");
extern s32 D_80125710;
extern SeqMarker D_80150360;
extern SeqMarker D_80150370;

void apply_audio_sequence(s32 sequence) __asm__("func_80079C20");

void apply_audio_sequence(s32 sequence) {
    s32 size;

    if (D_80125710 != sequence) {
        if (D_80125710 != -1) {
            stop_sequence_player();
        }
        size = gSequenceRomOffsets[sequence] - gSequenceRomOffsets[sequence - 1];
        rom_dma_read(gSequenceRomOffsets[sequence - 1], gSequenceBuffer, size);
        alCSeqNew(gAudioSequence, gSequenceBuffer, size);
        alCSeqNewMarker(gAudioSequence, &D_80150360, 0);
        alCSeqNewMarker(gAudioSequence, &D_80150370, -1);
        alCSPLoop(gAudioSequenceHandle, &D_80150360, &D_80150370, -1);
        alCSPSetSeq(gAudioSequenceHandle, gAudioSequence);
        alCSPSetBank(gAudioSequenceHandle, D_8015038C->bankArray[0]);
        alCSPPlay(gAudioSequenceHandle);
        D_80125710 = sequence;
    }
}
