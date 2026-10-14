#include "types.h"

#define FILTER_SCALE 0x4000

typedef struct ALLowPass {
    s16 cutoff;
    s16 gain;
    u8 pad04[4];
    s16 coefficients[16];
    u8 pad28[4];
    s32 first;
} ALLowPass;

void init_lpfilter(ALLowPass *filter)
{
    s32 i;
    s32 temporary;
    s16 cutoff;
    f64 normalized;
    f64 coefficient;

    temporary = filter->cutoff * FILTER_SCALE;
    cutoff = temporary >> 15;
    filter->gain = FILTER_SCALE - cutoff;
    filter->first = 1;
    for (i = 0; i < 8; i++) {
        filter->coefficients[i] = 0;
    }
    filter->coefficients[i++] = cutoff;
    coefficient = normalized = (f64)cutoff / FILTER_SCALE;
    for (; i < 16; i++) {
        coefficient *= normalized;
        filter->coefficients[i] = (s16)(coefficient * FILTER_SCALE);
    }
}
