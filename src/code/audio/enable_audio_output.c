#include "types.h"

extern void func_801053B0(s32 enabled);

void enable_audio_output(void) __asm__("func_800ABFB0");

void enable_audio_output(void)
{
    func_801053B0(1);
}
