#include "types.h"

typedef struct AudioDoneMessage {
    s32 value00;
    s32 frame;
} AudioDoneMessage;

extern s32 osRecvMesg(void *queue, void **message, s32 flags) __asm__("func_80119240");
extern s32 build_audio_frame_task(void *frame, s32 previous) __asm__("func_8007A5A4");
extern void audio_poll_dma_idle(s32 frame) __asm__("func_8007A758");
extern void func_8011C1A4(void *globals);
extern void func_8011D2F0(s32 value);
extern void *D_80125764;
extern u32 D_80125768;
extern void *D_801B4A48[3];
extern u8 gAudioGlobals[] __asm__("D_801502F0");
extern u8 gAudioCommandQueue[] __asm__("D_80152F90");
extern u8 gAudioDoneQueue[] __asm__("D_801B4A28");

void audio_thread_main(void *arg) __asm__("func_8007A470");
void audio_thread_main(void *arg) {
    s32 done = 0;
    s32 previous = 0;
    void *command = 0;
    AudioDoneMessage *message = 0;

    do {
        osRecvMesg(gAudioCommandQueue, &command, 1);
        switch ((s32)command) {
        case 1:
            if (build_audio_frame_task(D_801B4A48[D_80125768 % 3], previous) != 0) {
                osRecvMesg(gAudioDoneQueue, (void **)&message, 1);
                audio_poll_dma_idle(message->frame);
                previous = message->frame;
            }
            break;
        case 10:
            previous = 0;
            func_8011C1A4(gAudioGlobals);
            D_80125764 = 0;
            func_8011D2F0(0);
            break;
        }
    } while (!done);
}
