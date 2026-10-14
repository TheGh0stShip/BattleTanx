#include "types.h"

extern s32 gAudioLookupTable[] __asm__("D_8013227C");

s32 lookup_audio_table_stride_two(s32 index) __asm__("func_800AB61C");

s32 lookup_audio_table_stride_two(s32 index)
{
    return gAudioLookupTable[index * 2];
}
