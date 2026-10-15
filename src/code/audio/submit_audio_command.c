#include "types.h"
extern void enqueue_audio_command(void *queue, s16 value) __asm__("func_8011CB90");
extern void *gAudioCommandQueue __asm__("D_80150380");
extern void *dispatch_audio_commands(void *queue) __asm__("func_8011C300");
s32 submit_audio_command(s16 value) __asm__("func_800796B4");

s32 submit_audio_command(s16 value)
{
    enqueue_audio_command(gAudioCommandQueue, value);
    return dispatch_audio_commands(gAudioCommandQueue) != 0;
}
