#include "types.h"

typedef struct AudioTask {
    u32 type;
    u32 flags;
    u64 *ucodeBoot;
    u32 ucodeBootSize;
    u64 *ucode;
    u32 ucodeSize;
    u64 *ucodeData;
    u32 ucodeDataSize;
    u64 *dramStack;
    u32 dramStackSize;
    u64 *outputBuff;
    u64 *outputBuffSize;
    u64 *dataPtr;
    u32 dataSize;
    u64 *yieldDataPtr;
    u32 yieldDataSize;
} AudioTask;

typedef struct AudioFrameInfo {
    u32 outputBuffer;
    s16 frameSamples;
    u8 pad06[0x2];
    AudioTask task;
    u8 message[1];
} AudioFrameInfo;

typedef struct AudioOutputBuffer {
    u32 address;
    s16 samples;
} AudioOutputBuffer;

extern void clear_audio_dma_buffers(void) __asm__("func_8007A968");
extern u32 osAiGetLength(void) __asm__("func_80110480");
extern s32 audio_set_next_buffer(u32 address, s32 length) __asm__("func_801105F0");
extern u64 *audio_build_frame(u64 *commandList, s32 *commandCount, u32 outputBuffer, s16 samples)
    __asm__("func_8011DD48");
extern u32 audio_translate_address(u32 address) __asm__("func_80121F10");
extern u64 D_8010E160[];
extern u64 D_8010E230[];
extern u8 D_8010F660[];
extern u8 D_80145AA0[];
extern AudioTask *D_80125764;
extern s32 D_80125770;
extern void *D_80152A10;
extern s32 D_80152EE8;
extern u64 *D_80152EF0[2];
extern s32 D_801B4A40;

s32 build_audio_frame_task(AudioFrameInfo *frame, AudioOutputBuffer *previous) __asm__("func_8007A5A4");

s32 build_audio_frame_task(AudioFrameInfo *frame, AudioOutputBuffer *previous) {
    s32 commandCount;
    u32 outputBuffer;
    u64 *commandEnd;
    AudioTask *task;
    void *message;
    u64 **commandList;

    clear_audio_dma_buffers();
    outputBuffer = audio_translate_address(frame->outputBuffer);
    if (previous != 0) {
        audio_set_next_buffer(previous->address, previous->samples << 2);
    }
    frame->frameSamples = (D_801B4A40 - (osAiGetLength() >> 2) + 0x60) & 0xFFF0;
    if (frame->frameSamples < D_80152EE8) {
        frame->frameSamples = D_80152EE8;
    }
    commandEnd = audio_build_frame(D_80152EF0[D_80125770], &commandCount, outputBuffer, frame->frameSamples);
    if (commandCount == 0) {
        return 0;
    }
    commandList = &D_80152EF0[D_80125770];
    frame->task.type = 2;
    frame->task.flags = 0;
    frame->task.ucodeBoot = D_8010E160;
    frame->task.ucodeBootSize = (u32)D_8010E230 - (u32)D_8010E160;
    frame->task.ucode = (u64 *)D_8010F660;
    frame->task.ucodeData = (u64 *)D_80145AA0;
    frame->task.ucodeDataSize = 0x800;
    frame->task.dataPtr = *commandList;
    frame->task.dataSize = (commandEnd - *commandList) * sizeof(u64);
    task = &frame->task;
    message = frame->message;
    frame->task.yieldDataPtr = 0;
    frame->task.yieldDataSize = 0;
    frame->task.dramStack = 0;
    frame->task.dramStackSize = 0;
    frame->task.outputBuff = 0;
    frame->task.outputBuffSize = 0;
    while (D_80125764 != 0) {
    }
    D_80152A10 = message;
    D_80125764 = task;
    D_80125770 ^= 1;
    return 1;
}
