#include "types.h"
extern void enqueue_audio_command(s32 command, s32 value) __asm__("func_8011CB90");
extern void *D_80150380;
extern void *dispatch_audio_commands(void *queue) __asm__("func_8011C300");
s32 submit_audio_command(s32 command, s32 packedValue) __asm__("func_800796C0");
s32 submit_audio_command(s32 command, s32 packedValue) { enqueue_audio_command(command, packedValue >> 16); return dispatch_audio_commands(D_80150380) != 0; }
