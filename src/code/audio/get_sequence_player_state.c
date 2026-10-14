#include "types.h"

extern void *gAudioSequenceHandle __asm__("D_80150350");

extern s32 get_record_halfword_32(void *record) __asm__("func_80119B50");

s16 get_sequence_player_state(void) __asm__("func_80079D9C");

s16 get_sequence_player_state(void)
{
    return get_record_halfword_32(gAudioSequenceHandle);
}
