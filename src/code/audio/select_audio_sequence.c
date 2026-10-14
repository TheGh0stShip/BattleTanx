#include "types.h"

extern void apply_audio_sequence(s32 sequence) __asm__("func_80079C20");

void select_audio_sequence(s32 sequence) __asm__("func_80079BB4");

void select_audio_sequence(s32 sequence)
{
    apply_audio_sequence(sequence);
}
