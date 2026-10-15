#include "types.h"

typedef struct {
    s32 maxVVoices;
    s32 maxPVoices;
    s32 maxUpdates;
    s32 pad0C;
    void *(*dmaNew)(u8 **state);
    void *heap;
    s32 outputRate;
    s8 fxType;
    s32 pad20[2];
} AudioSynthConfig;

extern void audio_heap_init(void *heap, void *base, s32 size) __asm__("func_801121A0");
extern s32 audio_set_frequency(s32 frequency) __asm__("func_80110490");
extern void audio_synth_init(void *globals, AudioSynthConfig *config) __asm__("func_8011C1DC");
extern void *init_audio_dma_state(u8 **state) __asm__("func_8007A79C");
extern u8 gAudioGlobals[] __asm__("D_801502F0");
extern u8 gAudioHeap[] __asm__("D_80150340");
extern u8 gAudioHeapBuffer[] __asm__("D_80152FA8");
extern s32 gAudioMinFrameSamples __asm__("D_80152EE8");
extern s32 gAudioMaxFrameSamples __asm__("D_80152EF8");
extern u32 gAudioFrameSamples __asm__("D_801B4A40");

void init_audio_synth(s8 fxType) __asm__("func_80079DC8");

void init_audio_synth(s8 fxType) {
    AudioSynthConfig config;
    f32 samples;
    s32 count;

    audio_heap_init(gAudioHeap, gAudioHeapBuffer, 0x61A80);
    config.maxVVoices = 0x30;
    config.maxPVoices = 0x30;
    config.maxUpdates = 0xC4;
    config.dmaNew = init_audio_dma_state;
    config.fxType = fxType;
    config.outputRate = audio_set_frequency(22050);
    config.heap = gAudioHeap;
    audio_synth_init(gAudioGlobals, &config);
    samples = ((f32)config.outputRate * 2.0f) / 60.0f;
    count = (s32)samples;
    gAudioFrameSamples = count;
    if ((f32)(u32)count < samples) {
        gAudioFrameSamples = count + 1;
    }
    if (gAudioFrameSamples & 0xF) {
        gAudioFrameSamples = (gAudioFrameSamples & ~0xF) + 0x10;
    }
    gAudioMinFrameSamples = gAudioFrameSamples - 0x10;
    gAudioMaxFrameSamples = gAudioFrameSamples + 0x60;
}
