#include "types.h"

extern s32 gBitWindow __asm__("D_8035CD24");
extern s32 read_stream_bit(void) __asm__("func_800F58F0");

void read_bit_window(void) __asm__("func_800F5128");

void read_bit_window(void)
{
    s32 i;

    for (i = 0; i <= 16; i++) {
        gBitWindow = gBitWindow * 2 + read_stream_bit();
    }
}
