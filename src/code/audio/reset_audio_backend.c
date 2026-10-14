#include "types.h"
extern s32 D_80125710;
extern void reset_audio_backend(void) __asm__("func_8011B9E0");
void reset_audio_backend_state(void) __asm__("func_80079B88");
void reset_audio_backend_state(void) { D_80125710 = -1; reset_audio_backend(); }
