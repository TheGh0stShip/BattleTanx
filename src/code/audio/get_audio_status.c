#include "types.h"
extern s32 get_audio_status_impl(void) __asm__("func_80119B50");
s16 get_audio_status(void) __asm__("func_80079DA4");
s16 get_audio_status(void) { return get_audio_status_impl(); }
