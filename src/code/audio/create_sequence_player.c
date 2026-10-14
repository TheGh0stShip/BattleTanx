#include "types.h"

/* Layout of libaudio's ALSeqpConfig. */
typedef struct SeqPlayerConfig {
    s32 maxVoices;
    s32 maxEvents;
    u8 maxChannels;
    u8 debugFlags;
    void *heap;
    void *initOsc;
    void *updateOsc;
    void *stopOsc;
} SeqPlayerConfig;

extern u8 gAudioHeap[] __asm__("D_80150340");
extern void *gAudioSequenceHandle __asm__("D_80150350");
extern void *gAudioSequence __asm__("D_80150354");

extern void *alHeapDBAlloc(u8 *file, s32 line, void *heap, s32 num, s32 size) __asm__("func_80112140");
extern void alSeqpNew(void *seqp, SeqPlayerConfig *config) __asm__("func_8011B314");

void create_sequence_player(void) __asm__("func_80079EFC");

void create_sequence_player(void)
{
    SeqPlayerConfig config;

    config.maxVoices = 48;
    config.maxEvents = 64;
    config.maxChannels = 16;
    config.heap = gAudioHeap;
    config.initOsc = 0;
    config.updateOsc = 0;
    config.stopOsc = 0;
    config.debugFlags = 0;
    gAudioSequenceHandle = alHeapDBAlloc(0, 0, gAudioHeap, 1, 0x88);
    alSeqpNew(gAudioSequenceHandle, &config);
    gAudioSequence = alHeapDBAlloc(0, 0, gAudioHeap, 1, 0x1C);
}
