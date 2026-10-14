#include "lzari_state.h"

s32 lzari_decode(u32 sourceSize, u8 *source, u32 destinationSize, u8 *destination) __asm__("func_800F4F60");

/* Expand one LZARI stream; returns -1 when the header size is zero or does
 * not fit in destinationSize. */
s32 lzari_decode(u32 sourceSize, u8 *source, u32 destinationSize, u8 *destination)
{
    s32 i;
    s32 j;
    s32 k;
    s32 r;
    s32 c;
    u32 count;

    gLzariLow = 0;
    gLzariHigh = LZARI_Q4;
    gLzariValue = 0;
    gLzariBitBuffer = 0;
    gLzariBitMask = 0;
    gLzariSourceSize = sourceSize;
    gLzariSource = source;
    gLzariDestinationSize = destinationSize;
    gLzariDestination = destination;
    gLzariTextSize = *(u32 *)source;
    gLzariSource = source + 4;
    if (gLzariTextSize == 0 || destinationSize < gLzariTextSize) {
        return -1;
    }
    lzari_start_decode();
    lzari_start_model();
    for (i = 0; i < LZARI_N - LZARI_F; i++) {
        gLzariTextBuffer[i] = ' ';
    }
    r = LZARI_N - LZARI_F;
    for (count = 0; count < gLzariTextSize;) {
        c = lzari_decode_char();
        if (c < 256) {
            *gLzariDestination++ = c;
            gLzariTextBuffer[r++] = c;
            r &= LZARI_N - 1;
            count++;
        } else {
            i = (r - lzari_decode_position() - 1) & (LZARI_N - 1);
            j = c - 255 + LZARI_THRESHOLD;
            for (k = 0; k < j; k++) {
                c = gLzariTextBuffer[(i + k) & (LZARI_N - 1)];
                *gLzariDestination++ = c;
                gLzariTextBuffer[r++] = c;
                r &= LZARI_N - 1;
                count++;
            }
        }
    }
    return 0;
}
