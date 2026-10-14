#include "types.h"

typedef struct {
    u8 pad000[0x3E0];
    f32 value3E0;
    f32 value3E4;
} RampTarget;

#define MIN(a, b) ((a) < (b) ? (a) : (b))

void raise_value_pair_toward_limit(RampTarget *t, f32 x, f32 y) __asm__("func_8009F8EC");

/* Steps fields 0x3E0/0x3E4 up by their limit when below it, clamping to the limit. */
void raise_value_pair_toward_limit(RampTarget *t, f32 x, f32 y)
{
    if (t->value3E0 < x) {
        t->value3E0 += x;
        t->value3E0 = MIN(t->value3E0, x);
    }
    if (t->value3E4 < y) {
        t->value3E4 += y;
        t->value3E4 = MIN(t->value3E4, y);
    }
}
